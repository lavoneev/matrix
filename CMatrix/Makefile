CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
SOURCES = s21_*.c
SOURCES_TEST = tests/test*.c main.c
OBJECTS = $(SOURCES: .c=.o)
OBJECTS_TEST = test*.o main.o
TESTEXEC = tests/test

OS := $(shell uname -s)
ifeq ($(OS), Linux)
#CHECKFLAGS = -pthread -lcheck -lm -lsubunit -lrt
  CHECKFLAGS = -lm -lcheck -lsubunit
  LEAKY= valgrind -s
endif
ifeq ($(OS), Darwin)
  CHECKFLAGS = -lm -lcheck
  LEAKY= leaks --atExit --
endif

all: s21_matrix.a

s21_matrix.a: clean
	$(CC) $(CFLAGS) -c s21_*.c
	ar rcs s21_matrix.a s21_*.o
	rm -f *.o

test: clean
	$(CC) $(CFLAGS) -c $(SOURCES_TEST) $(SOURCES)
	$(CC) $(CFLAGS) --coverage -o $(TESTEXEC) $(SOURCES) $(OBJECTS_TEST) $(CHECKFLAGS)
	./$(TESTEXEC)

gcov_report: test
	lcov -t "gcov_s21_matrix" -o s21_matrix.info -c -d .
	genhtml -o report s21_matrix.info

clean:
	rm -rf *.o s21_matrix *.gcno *.gcda report s21_matrix.info .gitkeep *.a ./tests/test ./tests/*.gc*

autoformat:
	clang-format -i ./*.c ./*.h ./tests/*.c ./tests/*.h

style_check:
	clang-format -n ./*.c ./*.h ./tests/*.c ./tests/*.h

check:
#leaks -atExit -- ./s21_matrix
	valgrind --leak-check=full ./tests/test
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./s21_matrix

update:
	git reset --hard
	git pull

test_linux: all_linux check
	

push:
	git add --all
	git commit -ms
	git push --all

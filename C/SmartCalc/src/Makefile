CC = gcc
CFLAGS = -Wall -Werror -Wextra
C11 = -std=c11
OS = $(shell uname -s)
REPORT = gcov_report

all: SmartCalc

SmartCalc:
	make clean
	cd SmartCalcQT && qmake && make && make clean && rm Makefile && cd ..

install:
	make SmartCalc
	mkdir build && mv SmartCalcQT/SmartCalc.app build

uninstall:
	rm -rf build

clean:
	rm -rf *.o *.app *.a *.out *.info *.gcno *.gcda $(REPORT)
	cd SmartCalcQT && rm -rf *.o
	rm -rf *.dSYM/*
	rm -rf *.dSYM

dvi:
	open README.html

dist:
	rm -rf ../SmartCalc_archive/
	rm -rf SmartCalc_archive/
	mkdir SmartCalc_archive/
	mkdir SmartCalc_archive/src
	cp build/SmartCalc.app/Contents/MacOS/SmartCalc SmartCalc_archive/src/
	tar cvzf SmartCalc_archive.tgz SmartCalc_archive
	rm -rf *.tgz

test: clean
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) -fsanitize=address -lcheck test.c s21*.c -o test.out && ./test.out
else 
	$(CC) $(CFLAGS) -lrt -lpthread -lm -lsubunit -fsanitize=address -lcheck test.c s21*.c -o test.out && ./test.out
endif

gcov_report:
ifeq ($(OS), Darwin)
	$(CC) -fprofile-arcs -ftest-coverage test.c s21*.c -lcheck -o $(REPORT)
else
	$(CC) $(CFLAGS) -lrt -lpthread -lm -lsubunit -fsanitize=address -lcheck test.c s21*.c -o test.out && ./test.out
endif
	./$(REPORT)
	lcov -t report -o $(REPORT).info -c -d .
	genhtml -o report $(REPORT).info
	open ./report/index.html
	rm -rf *.gcno *.gcda $(REPORT).*
	rm $(REPORT)
	rm -rf *.dSYM

open:
ifeq ($(OS), Darwin)
	cd build && open SmartCalc.app
else
	cd build && xdg-open SmartCalc.app
endif

style:
	clang-format -n *.c *.h

leaks:
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test.out
else
	valgrind  --leak-check=full ./test.out
endif


	

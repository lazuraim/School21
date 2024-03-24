CC = g++
CFLAGS = -Wall -Werror -Wextra
OS := $(shell uname)

ifeq ($(OS),Linux)
TEST_FLAGS = -lgtest -lm -lpthread -lrt -fprofile-arcs -ftest-coverage
else
TEST_FLAGS = -lgtest -lm -lpthread -fprofile-arcs -ftest-coverage
endif

REPORT = gcov_report

all: install open

install:
	make clean
	mkdir build
	cp -rf smart_calc.pro build
	cp -rf qcustomplot.h build
	cp -rf qcustomplot.cc build
	cp -rf Controller build
	cp -rf View build
	cp -rf Model build
	cd build && qmake && make && make clean && rm Makefile

uninstall:
	rm -rf build

clean:
	rm -rf *.o *.app *.a *.out *.info *.gcno *.gcda $(REPORT) test
	rm -rf *.dSYM/*
	rm -rf *.dSYM

dvi:
	open README.html

dist:
	rm -rf ../smart_calc_archive/
	rm -rf smart_calc_archive/
	mkdir smart_calc_archive/
	mkdir smart_calc_archive/src
	cp build/smart_calc.app/Contents/MacOS/smart_calc smart_calc_archive/src/
	tar cvzf smart_calc_archive.tgz smart_calc_archive
	rm -rf *.tgz

test: clean
	g++ -std=c++17 -Wall -Werror -Wextra tests.cc $(TEST_FLAGS) -o test && ./test

gcov_report: test
	lcov -t "./$(REPORT)" -o $(REPORT).info --no-external -c -d . --ignore-errors mismatch
	genhtml -o report $(REPORT).info
	open ./report/index.html
	rm -rf *.gcno *.gcda $(REPORT).*
	rm $(REPORT)
	rm -rf *.dSYM

open:
ifeq ($(OS), Darwin)
	cd build && open smart_calc.app
else
	cd build && xdg-open smart_calc.app
endif

style:
	clang-format -n ./*/*.cc ./*/*.h *.cc *.h

correct_style:
	clang-format -i ./*/*.cc ./*/*.h *.cc *.h

leaks: test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test
else
	valgrind  --leak-check=full -s ./test
endif

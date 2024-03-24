CC = g++
CFLAGS = -std=c++17 -Wall -Werror -Wextra
TEST_LIBS = -lgtest -pthread
OS = $(shell uname -s)

MAP_TEST = tests/map_tests.cc
SET_TEST = tests/set_tests.cc
MULTISET_TEST = tests/multiset_tests.cc

all:

clean:
	rm -rf $(TARGET) *.o *.out test *.gcno *.gcda *.dSYM report gcov_report

test: clean
	$(CC) $(MAP_TEST) $(SET_TEST) $(MULTISET_TEST) -o test $(TEST_LIBS) $(CFLAGS)
	./test

gcov_report:
	$(CC) $(SOURCES) --coverage $(MAP_TEST) $(SET_TEST) $(MULTISET_TEST) -o gcov_report $(TEST_LIBS) $(CFLAGS)
	./gcov_report
	lcov -t report -o gcov_report.info -c -d . --no-external  --ignore-errors mismatch
	genhtml -o report gcov_report.info
	open ./report/index.html
	rm -rf *.gcno *.gcda *.dSYM gcov_report.* gcov_report

leaks: test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks -atExit -- ./test
else
	valgrind --leak-check=full ./test
endif

check_style:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.cc ./*/*.h
	rm -rf .clang-format

style:
	cp ../materials/linters/.clang-format ./
	clang-format -i ./*/*.cc ./*/*.h
	rm -rf .clang-format

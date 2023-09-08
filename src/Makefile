CC = g++
FLAGS = -Wextra -Werror -Wall -std=c++17
TESTFLAGS=-lgtest -lgtest_main
FILES = model/model.cc controller/controller.cc
TESTS = tests/*

all: uninstall install tests

install:
	mkdir build
	cd ./build; cmake ../CMakeLists.txt; cmake --build .
	open build/view.app/Contents/MacOS/view

uninstall:
	rm -rf build

dvi:
#	doxygen
	open ./html/index.html

dist:
	cd ..; tar -cvf archive.tar src

tests: clean
	g++ --coverage $(FLAGS) $(TESTS) $(FILES) $(TESTFLAGS) -o test
	./test

gcov_report: tests
	lcov --no-external -ignore-errors mismatch -t "test" -o report.info -c -d .
	genhtml -o report.html report.info
	rm *.gcda *.gcno
	open report.html/index.html 2>/dev/null

clean:
	rm -rf main *.dSYM test *.o *.a *.gcda *.gcno *.info *.out report .clang_format report.html build-* ../*tar

style:
	cp ../materials/linters/.clang-format ./
	clang-format -n tests/*.cc model/* controller/* view/*
	rm .clang-format

valgrind: tests
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=RESULT_VALGRIND.txt ./test



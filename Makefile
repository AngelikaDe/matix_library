CC=g++
CFLAGS= -std=c++11

LDFLAGS=-Wall -Wextra -Werror 

TARGET = MatrixProject
SRCS = s21_matrix_oop.cpp
OBJS = $(SRCS:.cpp=.o)

CFILES= tests/*.cc s21_matrix_oop.cpp
OFILES=$(CFILES:.cpp=.o)
TARGET = tests
LIB_NAME = s21_matrix_oop.a
LIB_FILES = s21_matrix_oop.o



$(TARGET): $(OFILES)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OFILES) -o $(TARGET) $(LIBFLAGS)


.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

style:
	clang-format -n *.c *.h --style=Google

gcov_report:
	./build/tests
	lcov -t "test_html" -o build/unit_test.info -c -d . --rc lcov_branch_coverage=1
	genhtml -o test_html build/unit_test.info
	open test_html/index.html

clean:
	rm -f $(OBJS) $(TARGET)
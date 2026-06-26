CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
LIBS = -lcheck -lsubunit -lm -lpthread

SRC = s21_string.c s21_sprintf.c
OBJ = $(SRC:.c=.o)
TEST_SRC = ./tests/s21_tests.c
LIB_NAME = s21_string.a

all: $(LIB_NAME)

$(LIB_NAME): $(OBJ)
	ar rcs $(LIB_NAME) $(OBJ)
	ranlib $(LIB_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(LIB_NAME)
	$(CC) $(CFLAGS) $(TEST_SRC) $(LIB_NAME) -o test_runner $(LIBS)
	./test_runner

gcov_report: clean
	$(CC) $(CFLAGS) --coverage $(SRC) $(TEST_SRC) -o test_runner $(LIBS)
	./test_runner
	lcov -t "s21_string_report" -o s21_string_report.info -c -d .
	genhtml -o report s21_string_report.info
	open report/index.html || xdg-open report/index.html || echo "Report generated in src/report/index.html"

clean:
	rm -rf *.o *.a test_runner report *.gcno *.gcda *.info

.PHONY: all clean test gcov_report
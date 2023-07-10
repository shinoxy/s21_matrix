CFLAGS = gcc -Wall -Wextra -Werror -g
ASAN_OPTIONS = detect_leaks=1

ifeq ($(shell uname -s), Linux)
	LFLAG += -lcheck -lpthread -lrt -lm -lsubunit
endif

all: s21_matrix.a

s21_matrix.a:
	$(CFLAGS) -c s21_*.c
	ar rc s21_matrix.a s21_*.o
	ranlib s21_matrix.a

test: clean s21_matrix.a
	$(CFLAGS) TEST.c -o test s21_matrix.a $(LFLAG)
	./test

leaks: test
	valgrind -s --leak-check=full --track-origins=yes  ./test

valgrind: clean TEST.c s21_matrix.a test
	valgrind  -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=valgrind.log ./test
	grep -e ERROR valgrind.log > leaks.info
	cat leaks.info

gcov_report: clean
	$(CFLAGS) s21_*.c TEST.c -o gcov_report --coverage $(LFLAG)
	./gcov_report
	rm -rf *test*.gc*
	gcov *s21_*.c
	lcov -d . -o gcov_report.info -c
	genhtml -o report gcov_report.info
	open report/index.html

style:
	clang-format -style=Google -i *.c *.h
	clang-format -style=Google -n *.c *.h

rebuild: clean all

clean:
	rm -f *.gcno *.gcda *.info *.gcov
	rm -f *.o *.a
	rm -rf report *.dSYM
	rm -f *.out
	rm -rf test
	rm -f gcov_report
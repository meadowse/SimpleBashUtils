OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	@FLAGS := -Wall -Werror -Wextra -std=c11
else
	@FLAGS := -Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE
endif

all: clean s21_cat

s21_cat:
	@gcc $(FLAGS) s21_cat.c -o s21_cat

clean:
	@rm -rf s21_cat

style:s21_cat
	@cp ../../materials/linters/CPPLINT.cfg ./
	@python3 ./../../materials/linters/cpplint.py --extensions=c s21_cat.c s21_cat.h
	@rm -f CPPLINT.cfg

leaks: s21_cat
	@leaks --atExit -- ./s21_cat -benst test_file/all_flag_tests/*

cppcheck: s21_cat
	@cppcheck --enable=all --suppress=missingIncludeSystem . s21_cat.c s21_cat.h

check: style cppcheck

test: s21_cat
	@bash test_cat.sh
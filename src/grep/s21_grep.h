#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

struct flags {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
};

int open_file(char *pattern, char *find_str);
void s21_grep(struct flags *flags, char *pattern, char *filename);

#endif  //  SRC_GREP_S21_GREP_H_

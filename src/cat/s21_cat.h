#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

void open_file(char* argv[], int b, int e, int n, int s, int t, int T, int E);
int s21_cat(int b, int e, int n, int s, int t, int T, int E, FILE* fp, int count);

#endif  //  SRC_CAT_S21_CAT_H_

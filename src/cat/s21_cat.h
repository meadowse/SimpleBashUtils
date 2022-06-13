#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>

void open_file(char* argv[], int b, int e, int n, int s, int t, int v);
void s21_cat(int b, int e, int n, int s, int t, int v, FILE* fp);

#endif  //  SRC_CAT_S21_CAT_H_

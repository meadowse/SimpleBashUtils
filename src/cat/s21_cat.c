#include "s21_cat.h"

int main(int argc, char *argv[]) {
    int rez, b = 0, e = 0, n = 0, s = 0, t = 0, T = 0, E = 0;
    const char* short_options = "beEstTn";
    const struct option long_options[] = {
        { "number-nonblank", no_argument, NULL, 'b' },
        { "number", no_argument, NULL, 'n' },
        { "squeeze-blank", no_argument, NULL, 's' },
        { NULL, 0, NULL, 0 }
    };
    while ((rez = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        switch (rez) {
            case 'b': {b = 1; break;};
            case 'e': {e = 1; break;};
            case 'E': {E = 1; break;};
            case 'n': {n = 1; break;};
            case 's': {s = 1; break;};
            case 't': {t = 1; break;};
            case 'T': {T = 1; break;};
        }
    }
    open_file(argv, b, e, n, s, t, T, E);
    return 0;
}

void open_file(char* argv[], int b, int e, int n, int s, int t, int T, int E) {
    FILE* fp;
    argv++;
    int result = 1;
    while (*argv) {
        if (*argv[0] == '-') {
            argv++;
        } else {
            if ((fp = fopen(*argv, "r")) == NULL) {
                argv++;
            } else {
                result = s21_cat(b, e, n, s, t, T, E, fp, result);
                argv++;
            }
        }
    }
}

int s21_cat(int b, int e, int n, int s, int t, int T, int E, FILE* fp, int count) {
    int current, prev = '\n';
    int temp = 0;
    while ((current = getc(fp)) != EOF) {
        if (s) {
            if (current == '\n') temp++;
            if (current != '\n') temp = 0;
        }
        if (b && temp < 3) {
            if ((prev == '\n' && !(current == '\n')) || count == 1) {
                printf("%6d\t", count);
                count++;
            }
        }
        if (n && !b && temp < 3) {
            if (prev == '\n' || count == 1) {
                printf("%6d\t", count);
                count++;
            }
        }
        if ((e || E) && temp < 3) {
            if ((t || e) && current >= 0 && current < 32 && current != '\n' && current != '\t') {
                printf("^%c", 64 + current);
            } else if ((t || T) && current == '\t') {
                printf("^I");
            } else if (current != '\n') {
                printf("%c", current);
            }
            if (current == '\n') {
                printf("$\n");
            }
            if (current != '\n') temp = 0;
        } else if ((t || T) && temp < 3) {
            if (!e && t && current >= 0 && current < 32 && current != '\n' && current != '\t') {
                printf("^%c", 64 + current);
            } else if (current != '\t' && current != '\n') {
                printf("%c", current);
            } else if (!e && !E && current == '\n') {
                printf("\n");
            }
            if (current == '\t') {
                printf("^I");
            }
            if (current != '\n') temp = 0;
        } else {
            if (!((e || E) && current == '\n') && temp < 3) {
                putchar(current);
            }
        }
        prev = current;
    }
    return count;
}

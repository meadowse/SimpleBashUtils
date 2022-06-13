#include "s21_grep.h"

int main(int argc, char** argv) {
    struct flags flags = {0};
    char find_str[4096] = {0};
    int rez = 0;
    const char* short_options = "e:ivclnhsf:o";
    while ((rez = getopt(argc, argv, short_options)) != -1) {
        switch (rez) {
            case 'e': flags.e = 1; snprintf(find_str, 4096, optarg); break;
            case 'i': flags.i = 1; break;
            case 'v': flags.v = 1; break;
            case 'c': flags.c = 1; break;
            case 'l': flags.l = 1; break;
            case 'n': flags.n = 1; break;
            case 'h': flags.h = 1; break;
            case 's': flags.s = 1; break;
            case 'f': flags.f = 1; snprintf(find_str, 4096, optarg); break;
            case 'o': flags.o = 1; break;
            default: printf("usage: grep [-eivclnhsfo]\n");
        }
    }
    if (argc >= 3) {
        char pattern[4096] = {0};
        int f_patt = 0;
        if (!flags.f && !flags.e) snprintf(pattern, 4096, argv[optind++]);
        if (flags.f) f_patt = open_file(pattern, find_str);
        if (!flags.f && flags.e) snprintf(pattern, 4096, find_str);
        if (f_patt != -1) {
            int file_c = 0;
            if (argc - optind > 1) file_c = 1;
            for (int i = optind; i < argc; i++) {
                if (file_c && !flags.h && !flags.l) printf("%s:", argv[i]);
                s21_grep(&flags, pattern, argv[i]);
            }
        }
    } else {
        printf("usage: grep [-eivclnhsfo]\n");
        printf("\t[-e pattern] [-f file]\n");
        printf("\t[pattern] [file ...]\n");
    }
    return 0;
}

int open_file(char *pattern, char *filename) {
    FILE *fp;
    fp = fopen(filename, "r");
    int i = 0;
    if (fp != NULL) {
        int c;
        while ((c = fgetc(fp)) != EOF) {
            if (c == 13 || c == 10) pattern[i++] = '|';
            if (c != 13 && c != 10) pattern[i++] = c;
        }
    } else {
        printf("Cannot open file.\n");
        i = -1;
    }
    if (pattern[i - 1] == '|') pattern[i - 1] = '\0';
    fclose(fp);
    return i;
}

void s21_grep(struct flags *flags, char *pattern, char *filename) {
    int cflags = REG_EXTENDED;
    regex_t reg;
    FILE* fp;
    fp = fopen(filename, "r");
    if (flags->i) cflags = REG_ICASE;
    if (fp != NULL) {
        regcomp(&reg, pattern, cflags);
        char text[4096] = {0};
        regmatch_t pmatch[1];
        int line_matches = 0, nline = 1;
        while (fgets(text, 4095, fp) != NULL) {
            int match = 0;
            int success = regexec(&reg, text, 1, pmatch, 0);
            if (strchr(text, '\n') == NULL) strcat(text, "\n");
            if (success == 0 && !flags->v) match = 1;
            if (success == REG_NOMATCH && flags->v) match = 1;
            if (match && !flags->l && !flags->c && flags->n) printf("%d:", nline);
            if (match && !flags->l && !flags->c && !flags->o) printf("%s", text);
            if (match && flags->o) {
                for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
                    printf("%c", text[i]);
                }
                printf("\n");
            }
            line_matches += match;
            nline++;
        }
        if (flags->l && line_matches > 0) printf("%s\n", filename);
        if (flags->c && !flags->l) printf("%d\n", line_matches);
        regfree(&reg);
        fclose(fp);
    } else {
        if (!flags->s) printf("Cannot open file.\n");
    }
}

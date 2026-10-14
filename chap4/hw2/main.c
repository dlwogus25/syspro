#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i, ch, line = 1;
    int number = 0;
    FILE *fp;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-n] file...\n", argv[0]);
        return 1;
    }

    i = 1;

    if (strcmp(argv[1], "-n") == 0) {
        number = 1;
        i = 2;
    }

    if (i >= argc) {
        fprintf(stderr, "Usage: %s [-n] file...\n", argv[0]);
        return 1;
    }

    for (; i < argc; i++) {
        fp = fopen(argv[i], "r");

        if (fp == NULL) {
            fprintf(stderr, "Error Open File: %s\n", argv[i]);
            continue;
        }

        if (number) {
            printf("%6d  ", line);
        }

        while ((ch = fgetc(fp)) != EOF) {
            putchar(ch);

            if (ch == '\n') {
                line++;
                if (number) {
                    printf("%6d  ", line);
                }
            }
        }

        fclose(fp);
    }

    return 0;
}

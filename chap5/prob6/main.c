#include <stdio.h>
#include "student.h"

int main(int argc, char *argv[])
{
    struct student rec;
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "How to use: %s FileName\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "wb");
    if (fp == NULL) {
        fprintf(stderr, "Error Open File\n");
        return 2;
    }

    printf("StudentID Name Score\n");

    while (scanf("%d %19s %hd", &rec.id, rec.name, &rec.score) == 3) {
        fwrite(&rec, sizeof(rec), 1, fp);
    }

    fclose(fp);
    return 0;
}

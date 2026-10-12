#include <stdio.h>

struct student {
    int id;
    char name[20];
    short score;
};

int main(int argc, char *argv[])
{
    struct student rec;
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "Error Open File\n");
        return 2;
    }

    printf("StudentID Name Score\n");

    while (fscanf(fp, "%d %19s %hd",
                  &rec.id, rec.name, &rec.score) == 3) {
        printf("%d %s %hd\n", rec.id, rec.name, rec.score);
    }

    fclose(fp);
    return 0;
}

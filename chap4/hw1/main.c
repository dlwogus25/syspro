#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    int ch;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
        return 1;
    }

    fp1 = fopen(argv[1], "r");
    if (fp1 == NULL) {
        fprintf(stderr, "Error Open File\n");
        return 2;
    }

    fp2 = fopen(argv[2], "a");
    if (fp2 == NULL) {
        fprintf(stderr, "Error Open File\n");
        fclose(fp1);
        return 3;
    }

    while ((ch = fgetc(fp1)) != EOF) {
        fputc(ch, fp2);
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}

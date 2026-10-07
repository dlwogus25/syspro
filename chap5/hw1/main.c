#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd;
    char savedText[10][100];
    char buf;
    char input[100];
    int line = 0;
    int col = 0;
    int n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(1);
    }

    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            savedText[line][col] = '\0';
            line++;
            col = 0;
        }
        else {
            if (col < 99) {
                savedText[line][col] = buf;
                col++;
            }
        }
    }

    if (col > 0) {
        savedText[line][col] = '\0';
        line++;
    }

    close(fd);

    printf("Input : ");
    scanf("%s", input);

    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < line; i++) {
            printf("%d: %s\n", i + 1, savedText[i]);
        }
    }

    else if (strchr(input, '-') != NULL) {
        int start, end;

        sscanf(input, "%d-%d", &start, &end);

        for (int i = start; i <= end; i++) {
            if (i >= 1 && i <= line)
                printf("%d: %s\n", i, savedText[i - 1]);
        }
    }

    else if (strchr(input, ',') != NULL) {
        char *token = strtok(input, ",");

        while (token != NULL) {
            n = atoi(token);

            if (n >= 1 && n <= line)
                printf("%d: %s\n", n, savedText[n - 1]);

            token = strtok(NULL, ",");
        }
    }

    else {
        n = atoi(input);

        if (n >= 1 && n <= line)
            printf("%d: %s\n", n, savedText[n - 1]);
    }

    return 0;
}

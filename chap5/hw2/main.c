#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;
    char savedText[10][100];
    char buf;
    int line = 0;
    int col = 0;

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

    for (int i = line - 1; i >= 0; i--) {
        printf("%s\n", savedText[i]);
    }

    return 0;
}

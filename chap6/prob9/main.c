#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    char buf[PATH_MAX];
    ssize_t len;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s linkname\n", argv[0]);
        return 1;
    }

    len = readlink(argv[1], buf, sizeof(buf));

    if (len == -1) {
        perror("readlink");
        return 1;
    }

    if (write(STDOUT_FILENO, buf, len) == -1) {
        perror("write");
        return 1;
    }

    write(STDOUT_FILENO, "\n", 1);

    return 0;
}

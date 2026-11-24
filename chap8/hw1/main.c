#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

int main(int argc, char *argv[])
{
    int i;

    if (argc < 2) {
        printf("Usage: %s [-e [NAME]] [-u] [-g] [-i] [-p]\n", argv[0]);
        return 1;
    }

    for (i = 1; i < argc; i++) {

        if (strcmp(argv[i], "-e") == 0) {

            if (i + 1 < argc && argv[i + 1][0] != '-') {
                char *value = getenv(argv[++i]);

                if (value != NULL)
                    printf("%s\n", value);
                else
                    printf("Environment variable not found\n");
            }
            else {
                char **env;

                for (env = environ; *env != NULL; env++)
                    printf("%s\n", *env);
            }
        }

        else if (strcmp(argv[i], "-u") == 0) {
            printf("Real UID: %d\n", getuid());
            printf("Effective UID: %d\n", geteuid());
        }

        else if (strcmp(argv[i], "-g") == 0) {
            printf("Real GID: %d\n", getgid());
            printf("Effective GID: %d\n", getegid());
        }

        else if (strcmp(argv[i], "-i") == 0) {
            printf("Process ID: %d\n", getpid());
        }

        else if (strcmp(argv[i], "-p") == 0) {
            printf("Parent Process ID: %d\n", getppid());
        }

        else {
            printf("Invalid option: %s\n", argv[i]);
            return 1;
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG 100

int main()
{
    char line[MAXLINE];
    char *args[MAXARG];
    char *saveptr;
    char *token;
    int i;
    int background;
    int len;
    pid_t pid;

    while (1) {
        printf("[Shell] ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        len = strlen(line);

        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == ' '))
            line[--len] = '\0';

        if (len == 0)
            continue;

        background = 0;

        if (line[len - 1] == '&') {
            background = 1;
            line[--len] = '\0';
        }

        i = 0;
        token = strtok_r(line, " \t", &saveptr);

        while (token != NULL && i < MAXARG - 1) {
            args[i++] = token;
            token = strtok_r(NULL, " \t", &saveptr);
        }

        args[i] = NULL;

        if (args[0] == NULL)
            continue;

        if (strcmp(args[0], "exit") == 0)
            break;

        pid = fork();

        if (pid == 0) {
            execvp(args[0], args);
            perror("execvp");
            exit(1);
        }
        else if (pid > 0) {
            if (background) {
                printf("[Background] PID = %d\n", pid);
            }
            else {
                waitpid(pid, NULL, 0);
            }
        }
        else {
            perror("fork");
        }
    }

    return 0;
}

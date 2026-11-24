#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAXLINE 1024
#define MAXARG 100

void execute(char *command)
{
    char *args[MAXARG];
    char *saveptr;
    char *token;
    char *input = NULL;
    char *output = NULL;
    int background = 0;
    int i = 0;
    int fd;
    pid_t pid;

    while (*command == ' ')
        command++;

    if (strlen(command) == 0)
        return;

    int len = strlen(command);

    while (len > 0 && command[len - 1] == ' ')
        command[--len] = '\0';

    if (len > 0 && command[len - 1] == '&') {
        background = 1;
        command[len - 1] = '\0';
    }

    token = strtok_r(command, " \t\n", &saveptr);

    while (token != NULL && i < MAXARG - 1) {
        if (strcmp(token, ">") == 0) {
            token = strtok_r(NULL, " \t\n", &saveptr);
            if (token != NULL)
                output = token;
        }
        else if (strcmp(token, "<") == 0) {
            token = strtok_r(NULL, " \t\n", &saveptr);
            if (token != NULL)
                input = token;
        }
        else {
            args[i++] = token;
        }

        token = strtok_r(NULL, " \t\n", &saveptr);
    }

    args[i] = NULL;

    if (args[0] == NULL)
        return;

    pid = fork();

    if (pid == 0) {
        if (input != NULL) {
            fd = open(input, O_RDONLY);
            if (fd < 0) {
                perror("open");
                exit(1);
            }
            dup2(fd, 0);
            close(fd);
        }

        if (output != NULL) {
            fd = open(output, O_CREAT | O_TRUNC | O_WRONLY, 0660);
            if (fd < 0) {
                perror("open");
                exit(1);
            }
            dup2(fd, 1);
            close(fd);
        }

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

int main()
{
    char line[MAXLINE];
    char *command;
    char *saveptr;

    while (1) {
        printf("[shell] ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        command = strtok_r(line, ";\n", &saveptr);

        while (command != NULL) {
            execute(command);
            command = strtok_r(NULL, ";\n", &saveptr);
        }
    }

    return 0;
}

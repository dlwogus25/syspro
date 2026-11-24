#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    int opt;
    int show_inode = 0;
    int show_slash = 0;
    int show_quotes = 0;
    const char *dirpath = ".";
    DIR *dp;
    struct dirent *entry;
    struct stat st;
    char path[PATH_MAX];

    while ((opt = getopt(argc, argv, "ipQ")) != -1) {
        switch (opt) {
        case 'i':
            show_inode = 1;
            break;
        case 'p':
            show_slash = 1;
            break;
        case 'Q':
            show_quotes = 1;
            break;
        default:
            fprintf(stderr, "Usage: %s [-i] [-p] [-Q] [directory]\n",
                    argv[0]);
            return 1;
        }
    }

    if (optind < argc)
        dirpath = argv[optind];

    dp = opendir(dirpath);
    if (dp == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL) {
        int is_dir = 0;

        if (snprintf(path, sizeof(path), "%s/%s",
                     dirpath, entry->d_name) >= sizeof(path))
            continue;

        if (lstat(path, &st) == -1) {
            perror("lstat");
            continue;
        }

        is_dir = S_ISDIR(st.st_mode);

        if (show_inode)
            printf("%7ld ", (long)st.st_ino);

        if (show_quotes)
            printf("\"%s\"", entry->d_name);
        else
            printf("%s", entry->d_name);

        if (show_slash && is_dir)
            printf("/");

        printf("\n");
    }

    closedir(dp);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *entry;
    struct stat st;
    char path[PATH_MAX];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s directory\n", argv[0]);
        return 1;
    }

    dp = opendir(argv[1]);
    if (dp == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL) {
        if (snprintf(path, sizeof(path), "%s/%s",
                     argv[1], entry->d_name) >= sizeof(path)) {
            continue;
        }

        if (lstat(path, &st) == -1) {
            perror("lstat");
            continue;
        }

        printf("%-20s %10ld %4ld %s",
               entry->d_name,
               (long)st.st_size,
               (long)st.st_nlink,
               ctime(&st.st_mtime));
    }

    closedir(dp);
    return 0;
}

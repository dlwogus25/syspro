#include <stdio.h>
#include <string.h>
#include "copy.h"

int main()
{
    char line[MAXLINE];
    char lines[5][MAXLINE];
    char temp[MAXLINE];
    int len[5];
    int i, j;
    int tempLen;

    for(i = 0; i < 5; i++) {
        gets(line);
        len[i] = strlen(line);
        copy(line, lines[i]);
    }

    for(i = 0; i < 4; i++) {
        for(j = i + 1; j < 5; j++) {
            if(len[i] > len[j]) {

                tempLen = len[i];
                len[i] = len[j];
                len[j] = tempLen;

                copy(lines[i], temp);
                copy(lines[j], lines[i]);
                copy(temp, lines[j]);
            }
        }
    }

    for(i = 0; i < 5; i++) {
        printf("%s\n", lines[i]);
    }

    return 0;
}

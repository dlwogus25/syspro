#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"
   int main (int argc, char *argv[])
{
   int fd;
   struct student record;
   if (argc < 2) {
      fprintf(stderr, "How to use: %s file\n", argv[0]);
      exit(1);
   }
}

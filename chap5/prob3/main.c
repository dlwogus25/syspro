#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

main(int argc, char *argv[])
{ 
   int fd1, fd2, n;
   char buf[BUFSIZ];
   if (argc != 3) { 
      fprintf(stderr,"How to use: %s file1 file2\n",        
               argv[0]); 
      exit(1); 
   }
}

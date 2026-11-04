#include <stdio.h>
#include <stdio.h>
static void exit_handler1(void), 
                 exit_handler2(void);

int main(void) 
{
if (atexit(exit_handler1) != 0)	
    perror("exit_handler1 X");
  if (atexit(exit_handler2) != 0) 	
     perror("exit_handler2 X");
  printf("main end\n");
 exit(0);
}
static void exit_handler1(void) 
{
   printf("Firstblind\n");
}

static void exit_handler2(void) 
{
  printf("Secondblind\n");
}


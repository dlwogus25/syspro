#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main()
{
   printf("%d(%s) \n", getuid(), getpwuid(getuid())->pw_name);
   printf("%d(%s) \n", geteuid(), getpwuid(geteuid())->pw_name);
   printf("%d(%s) \n", getgid(), getgrgid(getgid())->gr_name);
   printf("%d(%s) \n", getegid(), getgrgid(getegid())->gr_name);
}


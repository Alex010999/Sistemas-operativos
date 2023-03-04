#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main ()
{
  pid_t pid_A;
  int status;
  
  //Father process
  printf("%d\n", pid_A);
  
  execl("/home/alex/Desktop/OS/hello_world", "", NULL);
  perror("execl ha fallado");
  return 0;
  
}

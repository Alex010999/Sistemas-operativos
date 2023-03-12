#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
  pid_t pid_B, pid_C, pid_E;
  int status;
  
  pid_B = fork();
  
  //Child process
  if( pid_B == 0)
  {
    sleep(3);
    return 1;
  }
  else
  {
    pid_C = fork();
    
    if(pid_C == 0)
    {
      sleep(1);
      return 2;
    }
    else 
    {
      pid_E = fork();
      
      if (pid_E == 0)
      {
        return 3;
      }
    }
  }
  
  if (pid_B > 0)
  {
    waitpid(pid_B, &status, 0);
    printf("El proceso B ha terminado con el status: %d.\n", WEXITSTATUS(status));
  }
  
  if (pid_C > 0)
  {
    waitpid(pid_C, &status, 0);
    printf("El proceso C ha terminado con el status: %d.\n", WEXITSTATUS(status));
  }
  
  if (pid_E > 0)
  {
    waitpid(pid_E, &status, 0);
    printf("El proceso E ha terminado con el status: %d.\n", WEXITSTATUS(status));
  }
  
  return 0;
}

  
  

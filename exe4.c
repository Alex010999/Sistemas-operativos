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
  pid_t pid_D, pid_E, pid_F;
  int status;
  int fd, n;
  
  pid_D = fork();
  
  //Child process
  if( pid_D == 0)
  {
    return 2;
  }
  else
  {
    pid_F = fork();
    
    if(pid_F == 0)
    {
      return 14;
    }
    else
    {
      pid_E = fork();
      
      if(pid_E == 0)
      {
        return 13;
      }
    }
  }
  
  if (pid_F > 0)
  {
    
    float res = 0;

    waitpid(pid_D, &status, 0);
    res = (float) WEXITSTATUS(status)*2-1;
    
    waitpid(pid_F, &status, 0);
    res = (res + (float)WEXITSTATUS(status))/100;
    
    waitpid(pid_E, &status, 0);
    res = (res + (float)WEXITSTATUS(status))/1000;
    
    printf("Resultado: %f\n", res);
    
    return 0;
    
  }

  return 0;
}

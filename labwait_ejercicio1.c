#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

int main ()
{
  pid_t pid_L, pid_D;
	
  int status, num_hijos_term, i;
	
  pid_D = fork();
	
  if (pid_D == 0)
  {
    sleep(1);
    printf("Termine mi ejecuciòn\n");
    printf("pid: %d\n", getpid());
    printf("pid de mi padre: %d\n", getppid());
    exit(EXIT_SUCCESS);
  }
  else 
  {
    pid_L = fork();
    if (pid_L == 0)
    {
      sleep(3);
      printf("Termine mi ejecuciòn\n");
      printf("pid: %d\n", getpid());
      printf("pid de mi padre: %d\n", getppid());
      exit(EXIT_SUCCESS);
    }
  }
  
  if (pid_L > 0)
  {
    pid_D = wait(&status);
    printf("Uno de mis hijos ha terminado su ejecucion\n");
  }
  return 0;
}

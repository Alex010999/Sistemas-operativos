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
  pid_t pid_A, pid_B, pid_C;
  int statusB;
  int fd, n;
  
  pid_B = fork();
  
  //Child process
  if( pid_B == 0)
  {
    printf("Hijo B");
    printf("Mi pid es: %d", getpid());
    printf("El pid de mi padre es : %d", getppid());
    execl("procesoB", "", NULL);
    perror("execl ha fallado");
    return 3;
  }
  else
  {
    pid_C = fork();
    
    if(pid_C == 0)
    {
      sleep(3);
      printf("Hijo C ");
      printf("Mi pid es: %d", getpid());
      printf("El pid de mi padre es : %d", getppid());
      return 0;
    }
  } 
  else 
  {
    waitpid(pid_B, &statusB, 0);
    
    if (WIFEXITED(statusB))
    {
      printf("El valor de retorno de B es %d", WEXITSTATUS(statusB));
    }
    else 
    {
      printf("el proceso B no termin[o bien");
    }
    
    fd = open("enteros.txt", 1)
    
    n = read(fd, doc, sizeof(doc));
    
    printf("%d\n", doc);
    
    close(fd);
    
    return 0;
    
  }
  
  
  /*(if (pid_A > 0)
  {
    waitpid(pid_B, &status, 0);
    if (WEXITSTATUS(status) == 0)
    {
      printf("El proceso M ha terminado con el status: %d.\n", WEXITSTATUS(status));
    }
    fd = open("")
  }
  */
  
  return 0;
}

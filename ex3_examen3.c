#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler_sigusr1(int signum)
{
  printf("Senal 1 recibida");
}

void handler_sigusr2(int signum)
{
  printf("Senal 2 recibida");
}

int main()
{
  pid_t pid_Q, pid_V, pid_R, pid_P;
  signal(SIGUSR1, handler_sigusr1);
  signal(SIGUSR2, handler_sigusr2);
  
// Crear proceso hijo Q
  pid_Q = fork();
  if (pid_Q < 0) {
      fprintf(stderr, "Error al crear proceso hijo Q\n");
      exit(EXIT_FAILURE);
  } else if (pid_Q == 0) { // Proceso hijo Q
      kill(pid_M, SIGUSR1)
      alarm(8);
      pause();
      exit(EXIT_SUCCESS);
  }

  // Crear proceso hijo V
  pid_V = fork();
  if (pid_V < 0) {
       fprintf(stderr, "Error al crear proceso hijo V\n");
       exit(EXIT_FAILURE);
  } else if (pid_V == 0) { // Proceso hijo V
      kill(pid_M, SIGUSR2)
      alarm(4);
      pause();
      exit(EXIT_SUCCESS);
  }
  
  // Crear proceso hijo R
  pid_R = fork();
  if (pid_R < 0) {
       fprintf(stderr, "Error al crear proceso hijo R\n");
       exit(EXIT_FAILURE);
  } else if (pid_R == 0) { // Proceso hijo R
      while(1)
      {
        printf("ID: %d.\n", getpid());
      }
  }
  
  // Crear proceso hijo P
  pid_P = fork();
  if (pid_P < 0) {
       fprintf(stderr, "Error al crear proceso hijo P\n");
       exit(EXIT_FAILURE);
  } else if (pid_P == 0) { // Proceso hijo P
      while(1)
      {
        printf("ID: %d.\n", getpid());
        
      }
  }
  
}

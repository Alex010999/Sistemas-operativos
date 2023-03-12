#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

int main (){
  int i, status;
  pid_t pid;
  int num_hijos_term = 0;
  int aleatorio;
  
  srand(time(NULL));
  
  for(i=0; i <3; i++){
    pid = fork();
    if(pid < 0) {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    else if (pid == 0){ //Proceso hijo
      printf("Proceso hijo");
      printf("pid: %d\n", getpid());
      aleatorio = rand() % 200;
      printf("Numero aleatorio = %d\n\n", aleatorio);
      exit(EXIT_SUCCESS);
    }
  }
  
  for(i = 0; i<3; i++){
    pid = wait(&status);
    if(WIFEXITED(status)){
      num_hijos_term++;
      printf("El proceso hijo %d termino correctamente.\n", pid);
    }
  }
  
  printf("Numero de procesos hijo que terminaron correctamente: %d\n", num_hijos_term);
  
  return 0;
}

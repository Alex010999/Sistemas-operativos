#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

#define SIZE 1000
int main()
{
  int fd, n;
  int enteros[SIZE];
  int i;
  
  for(i = 0; i < SIZE; i++)
  {
    enteros[i] = i + 1;
  }
  
  fd = creat("enteros.txt", 777);
  
  n = write(fd, &enteros, sizeof(enteros));
  
  close(fd);

}


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
	pid_t pid;
	
	//variables hijo
	int n, fd;
	int A[5] = {1,2,3,4,5};
	
	//variables padre
	int m, md;
	int B[5];
	
	pid = fork();
	
	//Child process
	if(pid == 0)
	{
	  fd = creat("datos.txt", 777);
	  
	  n = write(fd, A, sizeof(A));
	
	if(fd < 0)
	{
	  perror("Error:");
	}
		
        printf("se escribio en el archivo\n");
		
      	close(fd);
	}
	//return 0;
	
	if (pid > 0)
	{
	  sleep(3);
	  md = open("datos.txt", 0);
		
	  m = read(md, B, sizeof(B));
		
	  if(md < 0)
	  {
	    perror("Error:");
	  }
		
	  for(int i=0; i <5; i++)
	  {
	    printf("A[%d] %d. \n", i, B[i]);
	  }
		
	  close(md);
        }
	return 0;
}


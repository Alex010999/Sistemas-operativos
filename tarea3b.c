#include <stdio.h>
#include <math.h>
#include<errno.h>

int verf(int fd){
    if( fd < 0 )
     {
        if( errno == EAGAIN )
        {
            printf("Archivo bloqueado.\n");
            exit(1);
        }
        else if( errno == EACCES )
        {
            printf("Problema de permisos del archivo.\n");
            exit(1);
        }
        else if( errno == EBADF )
        {
            printf("Mal descriptor del archivo.\n");
            exit(1);
        }
        else
        {
            printf("Error desconocido.\n");
            exit(1);
        }
     }

}


int main()
{
    int fd, n;
    float value[4]={32.5,34.5, 5.5, 7.5};

    fd = creat("datos.txt", 777);

    n = write(fd, &value, sizeof(value));

    verf(fd);
    verf(n);

    close(fd);
    return 0;
    

    //printf("%d", n);
    //close(fd);
}
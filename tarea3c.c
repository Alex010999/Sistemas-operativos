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
    int fd;
    float n;
    float doc [4];

    fd = open("datos.txt", 1);

    n = read(fd, doc, sizeof(doc));
    printf("%d\n", doc);
    
    verf(fd);
    verf(n);

    //printf("%d", n);
    //close(fd);
}
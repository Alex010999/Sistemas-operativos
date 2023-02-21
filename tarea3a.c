#include <stdio.h>
#include <errno.h>

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

    printf("El valor es positivo. ");

}


int main()
{

    int fd;

    fd = open("archivo.txt", 1);
    //se va a imprimir un error desconocido ya que no se va a
    //encontrar el archivo determinado 

    verf(fd);
}
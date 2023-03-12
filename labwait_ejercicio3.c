
  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid_A, pid_B, pid_C, pid_D;
    int status;

    // Crear proceso hijo A
    pid_A = fork();
    if (pid_A < 0) {
        fprintf(stderr, "Error al crear proceso hijo A\n");
        exit(1);
    } else if (pid_A == 0) {  
        // Código del proceso hijo A
        pid_D = fork();
        if (pid_D < 0) {
            fprintf(stderr, "Error al crear proceso hijo D\n");
            exit(1);
        } else if (pid_D == 0) {
            // Código del proceso hijo D
            printf("Soy D y mi PID es %d\n", getpid());
            printf("El pid de mi padre es: %d\n\n", getppid());
            system("ls");
        } else {
            // Código del proceso hijo A
            waitpid(pid_D, &status, 0);
            printf("Soy A y mi PID es %d\n", getpid());
            printf("El pid de mi padre es: %d\n\n", getppid());
            system("rm -r new_folder");
        }
    } else {
        // Código del proceso padre
        // Crear proceso hijo B
        pid_B = fork();
        if (pid_B < 0) {
            fprintf(stderr, "Error al crear proceso hijo B\n");
            exit(1);
        } else if (pid_B == 0) {
            // Código del proceso hijo B
            printf("Soy B y mi PID es %d\n", getpid());
            printf("El pid de mi padre es: %d\n\n", getppid());
            system("mkdir new_folder");
        } else {
            // Código del proceso padre
            // Crear proceso hijo C
            pid_C = fork();
            if (pid_C < 0) {
                fprintf(stderr, "Error al crear proceso hijo C\n");
                exit(1);
            } else if (pid_C == 0) {
                // Código del proceso hijo C
                printf("Soy C y mi PID es %d\n", getpid());
                printf("El pid de mi padre es: %d\n\n", getppid());
                system("ls");
            } else {
                // Código del proceso padre
                // Esperar a que termine A
                waitpid(pid_A, &status, 0);
                // Ejecutar C
                printf("Soy el padre y mi PID es %d\n", getpid());
                printf("Ejecutando proceso C...\n");
                waitpid(pid_C, &status, 0);
                // Ejecutar B
                printf("Ejecutando proceso B...\n");
                waitpid(pid_B, &status, 0);
                // Imprimir mensaje y ejecutar ls
                printf("Soy M y mi PID es %d\n", getpid());
                system("ls");
            }
        }
    }
    return 0;
}

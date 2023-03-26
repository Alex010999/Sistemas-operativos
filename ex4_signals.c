#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void sig_handler(int signo) {
    if (signo == SIGALRM) {
        printf("Alarma recibida\n");
        exit(1);
    }
}

int main() {
    pid_t pidB, pidC;
    int status;

    // Establecer manejador de señal para SIGALRM
    if (signal(SIGALRM, sig_handler) == SIG_ERR) {
        perror("Error al establecer el manejador de señal");
        exit(1);
    }

    // Crear proceso B
    pidB = fork();

    if (pidB < 0) {
        perror("Error al crear el proceso hijo B");
        exit(1);
    } else if (pidB == 0) {
        // Código del proceso hijo B

        sleep(1); // Dormir por 1 segundo

        // Matar al proceso C
        pidC = getpid() + 1;
        kill(pidC, SIGKILL);

        // Esperar a recibir una señal
        while (1) {
            printf("Esperando una señal\n");
            sleep(1);
        }
    } else {
        // Código del proceso padre A

        // Establecer una alarma para que suene en 5 segundos
        alarm(5);

        // Crear proceso C
        pidC = fork();

        if (pidC < 0) {
            perror("Error al crear el proceso hijo C");
            exit(1);
        } else if (pidC == 0) {
            // Código del proceso hijo C

            // Esperar a recibir una señal
            while (1) {
                printf("Esperando una señal\n");
                sleep(1);
            }
        } else {
            // Esperar a que el proceso hijo B termine
            waitpid(pidB, &status, 0);

            printf("El proceso hijo B ha terminado\n");

            // Esperar a que el proceso hijo C termine
            waitpid(pidC, &status, 0);

            printf("El proceso hijo C ha terminado\n");
        }
    }

    return 0;
}

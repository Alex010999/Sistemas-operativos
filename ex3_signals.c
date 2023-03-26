#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

void handler_sigusr1(int sig) {
    printf("Recibi la señal SIGUSR1, mi pid es %d y el pid de mi padre es %d\n", getpid(), getppid());
    kill(getpid() + 1, SIGUSR2); // Enviar señal SIGUSR2 al siguiente proceso hijo
}

void handler_sigusr2(int sig) {
    printf("Recibi la señal SIGUSR2, mi pid es %d y el pid de mi padre es %d\n", getpid(), getppid());
}

int main() {
    pid_t pid_a, pid_b;
    signal(SIGUSR1, handler_sigusr1);
    signal(SIGUSR2, handler_sigusr2);

    // Crear proceso hijo A
    pid_a = fork();
    if (pid_a < 0) {
        fprintf(stderr, "Error al crear proceso hijo A\n");
        exit(EXIT_FAILURE);
    } else if (pid_a == 0) { // Proceso hijo A
        pause(); // Esperar señal SIGUSR1 del padre
        exit(EXIT_SUCCESS);
    }

    // Crear proceso hijo B
    pid_b = fork();
    if (pid_b < 0) {
        fprintf(stderr, "Error al crear proceso hijo B\n");
        exit(EXIT_FAILURE);
    } else if (pid_b == 0) { // Proceso hijo B
        pause(); // Esperar señal SIGUSR2 de A
        exit(EXIT_SUCCESS);
    }

    // Proceso padre M
    printf("Esperando 3 segundos para enviar señal SIGUSR1 a A...\n");
    sleep(3); // Esperar 3 segundos
    kill(pid_a, SIGUSR1); // Enviar señal SIGUSR1 a A

    // Esperar a que ambos hijos terminen
    int status;
    waitpid(pid_a, &status, 0);
    waitpid(pid_b, &status, 0);

    printf("Mis hijos han terminado\n");
    return 0;
}

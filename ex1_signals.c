#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int sig) {
    printf("El usuario presionó CTRL + C\n");
    sleep(3);
}

int main() {
    signal(SIGINT, sigint_handler); // registrar manejador de señal

    while (1) {
        printf("PID: %d\n", getpid());
        sleep(1);
    }

    return 0;
}

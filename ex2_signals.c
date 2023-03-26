#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {

    printf("Transcurrieron 3 segundos\n");
    exit(0);
    
}

int main() {

    signal(SIGALRM, handler);
    alarm(3);
    pause();
    
    return 0;
}

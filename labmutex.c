#include <stdio.h>//Abraham Yair Silva Figueroa 
#include <stdlib.h>//Abraham Yair Silva Figueroa 
#include <pthread.h>// Aldo Maldonado Hernandez
#include <stdbool.h>// Aldo Maldonado Hernandez
#include <sys/time.h>// Aldo Serrano Rugerio
#include <unistd.h>// Aldo Serrano Rugerio
#include <time.h>//Alejandro Orellan Leal

#define MAX_QUEUE_SIZE 100//Alejandro Orellan Leal

int counter = 1;//Alejandro Sanchez Gonzalez
bool finish = false;//Alejandro Sanchez Gonzalez
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;//Angel Adrian Pimienta Flores
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//Angel Adrian Pimienta Flores

typedef struct {//Bruno Marquez River
    int values[MAX_QUEUE_SIZE];//Bruno Marquez River
    int front;//Carlos Rodrigo Cortes 
    int rear;//Carlos Rodrigo Cortes 
    int size;// Cecilia Soriano Tochimani
} Queue;// Cecilia Soriano Tochimani

Queue odd_queue, even_queue;// Celeste Isabel Alonso Garcia 


void* print_odd_numbers(void* arg);// Celeste Isabel Alonso Garcia 
void* print_even_numbers(void* arg);//Daniel Laug Velazquez 
void* timer_thread(void* arg);//Daniel Laug Velazquez 
void initialize_queues(Queue* odd, Queue* even);//David Mayorga Castelan 
void enqueue(Queue* q, int value);//David Mayorga Castelan 
int dequeue(Queue* q);//Diego Gasparis Escobedo
bool is_empty(Queue* q);//Diego Gasparis Escobedo
bool is_full(Queue* q);// Efrain Gomez Arcive

int main()// Efrain Gomez Arcive
{
   
    initialize_queues(&odd_queue, &even_queue);//Emiliano Mixali Tofas Rodriguez

    pthread_t odd_thread, even_thread, timer_thread_id;//Emiliano Mixali Tofas Rodriguez
    pthread_create(&odd_thread, NULL, print_odd_numbers, NULL);//Estrella Jissel Verdiguel Colin
    pthread_create(&even_thread, NULL, print_even_numbers, NULL);//Estrella Jissel Verdiguel Colin
    pthread_create(&timer_thread_id, NULL, &timer_thread, NULL);//Eugenie Marie Christine Barriere

  
    pthread_join(odd_thread, NULL);//Eugenie Marie Christine Barriere
    pthread_join(even_thread, NULL);// Fernando Ahuatzin Gallardo
    pthread_join(timer_thread_id, NULL);// Fernando Ahuatzin Gallardo

    pthread_mutex_destroy(&mutex);//Fernando Uriel Perez Meneses
    pthread_cond_destroy(&condition);//Fernando Uriel Perez Meneses

    return 0;//Humberto Alejandro Zepeda Gonzalez 
}

void* print_odd_numbers(void* arg)//Humberto Alejandro Zepeda Gonzalez 
{
    while (!finish) {//Itzel Xhunaxhi Flores Ordaz 
     
        int value = counter;//Itzel Xhunaxhi Flores Ordaz 
        counter += 2;// Jesus Eduardo Zenteno Rodriguez 

      
        pthread_mutex_lock(&mutex);// Jesus Eduardo Zenteno Rodriguez 
        while (is_full(&odd_queue)) {;//Jesus Fernando Armendariz Zarate
            pthread_cond_wait(&condition, &mutex);;//Jesus Fernando Armendariz Zarate
        }
        enqueue(&odd_queue, value);//Jorge Luis Tovar Arriaga
        pthread_cond_signal(&condition);//Jorge Luis Tovar Arriaga
        pthread_mutex_unlock(&mutex);//Jose Andres Garcia Maceda

        
        printf("Hilo impar : %d\n", value);//Jose Andres Garcia Maceda
        fflush(stdout);//Jose Arrojo Ponce
    }

    return NULL;//Jose Arrojo Ponce
}

void* print_even_numbers(void* arg)// Juan Carlos Sanchez Bronca
{
    while (!finish) {// Juan Carlos Sanchez Bronca
        
        int value = counter;//Luis Fernando Cesar Denicia 
        counter += 2;//Luis Fernando Cesar Denicia 

      
        pthread_mutex_lock(&mutex);//Manuel Arturo Perez Alpuche

        while (is_full(&even_queue)) {//Manuel Arturo Perez Alpuche

            pthread_cond_wait(&condition, &mutex);//Marco Antonio Manzo Ruiz
        }
        enqueue(&even_queue, value);//Marco Antonio Manzo Ruiz
        pthread_cond_signal(&condition);//Marco Antonio Manzo Ruiz
        pthread_mutex_unlock(&mutex);//Marco Antonio Manzo Ruiz
       
        printf("Hilo Par : %d\n", value);//Marco Antonio Manzo Ruiz
        fflush(stdout);//Marco Antonio Manzo Ruiz

     
        pthread_mutex_lock(&mutex);//Melisa Sampieri Espinoza
        if (counter > 1000 && is_empty(&odd_queue) && is_empty(&even_queue)) {//Melisa Sampieri Espinoza
            finish = true;//Melisa Sampieri Espinoza
            pthread_cond_broadcast(&condition);//Melisa Sampieri Espinoza
        }
        pthread_mutex_unlock(&mutex);// Nina Maeva Mazadiego Cortes 
    }
    return NULL;
}


void* timer_thread(void* arg)// Nina Maeva Mazadiego Cortes 
{
struct timeval start_time, end_time;// Nina Maeva Mazadiego Cortes 
gettimeofday(&start_time, NULL);// Nina Maeva Mazadiego Cortes 
while (!finish) {// Nina Maeva Mazadiego Cortes 
gettimeofday(&end_time, NULL);//Pedro Escobedo Straffon 
long elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + end_time.tv_usec - start_time.tv_usec;
    if (elapsed_time > 500000) { ////Pedro Escobedo Straffon 
    
        pthread_mutex_lock(&mutex);//Pedro Escobedo Straffon 
        finish = true;//Pedro Escobedo Straffon 
        pthread_cond_broadcast(&condition);//Pedro Escobedo Straffon 
        pthread_mutex_unlock(&mutex);//Pedro Escobedo Straffon 
    }

    usleep(1000); //Pedro Escobedo Straffon 
}

return NULL;
}

void initialize_queues(Queue* odd, Queue* even)//Rafael Eduardo Rivero Mejia 
{
odd->front = 0;//Rafael Eduardo Rivero Mejia 
odd->rear = -1;//Rafael Eduardo Rivero Mejia 
odd->size = 0;//Rafael Eduardo Rivero Mejia 
even->front = 0;//Rafael Eduardo Rivero Mejia 
even->rear = -1;//Rafael Eduardo Rivero Mejia 
even->size = 0;//Ricardo Ladislao Martinez 
}

void enqueue(Queue* q, int value)//Ricardo Ladislao Martinez 
{
if (!is_full(q)) {//Ricardo Ladislao Martinez 
q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;//Ricardo Ladislao Martinez 
q->values[q->rear] = value;//Ricardo Ladislao Martinez 
q->size++;//Ricardo Ladislao Martinez 
}
}

int dequeue(Queue* q)//Ruben Dario Suarez Diaz
{
if (!is_empty(q)) {//Ruben Dario Suarez Diaz
int value = q->values[q->front];//Ruben Dario Suarez Diaz
q->front = (q->front + 1) % MAX_QUEUE_SIZE;//Ruben Dario Suarez Diaz
q->size--;//Ruben Dario Suarez Diaz
return value;
}
return -1;
}

bool is_empty(Queue* q)//Ximena Vazquez Mellado Flores
{
return q->size == 0;//Ximena Vazquez Mellado Flores
}

bool is_full(Queue* q)//Ximena Vazquez Mellado Flores
{
return q->size == MAX_QUEUE_SIZE;//Ximena Vazquez Mellado Flores
}
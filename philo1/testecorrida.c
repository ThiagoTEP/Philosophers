#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include <semaphore.h> 

#define THREADS 40 //quantas thread quero ter

long compartilhada = 0; //memoria compartilhada
//pthread_mutex_t mutex; //mutex
sem_t mutex;

void *threadFunc(void *arg)
{
    int a, b;
    for(long j = 0; j < 1000000; j++)
    {
        //pthread_mutex_lock(&mutex); //MUTEX
        sem_wait(&mutex); //SEMAFORO
        a = compartilhada;
        b = 1;
        compartilhada = a + b; //incrementa 1(condicao de corrida)
        //pthread_mutex_unlock(&mutex); //MUTEX
        sem_post(&mutex);//SEMAFORO
    }
}

int main(void)
{
    pthread_t t[THREADS];
    int s;

    //pthread_mutex_init(&mutex, NULL);
    sem_init(&mutex, 0 , 1);
    

    for(int i = 0; i < THREADS; ++i)
    {
        s = pthread_create(&t[i], NULL, threadFunc, NULL);
        if (s != 0)
        {
            perror("pthread_create");
            exit(1);
        }
    }

    for(int i = 0; i < THREADS; ++i)
    {
        s = pthread_join(t[i], NULL);
    }

    printf("Compartilhada = %ld\n", compartilhada);

    //pthread_mutex_destroy(&mutex);
    sem_destroy(&mutex);

    return 0;
}
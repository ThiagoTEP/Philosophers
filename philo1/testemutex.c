#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_t rotina[2];
pthread_mutex_t lock;

void *rotina_f1(void *p_param)
{
    int *valor = (int *)p_param;

    for(int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&lock);
        int tmp = *valor;
        tmp++;
        printf("f1 id : %lu, valor %d\n\n", pthread_self(), *valor);

        *valor = tmp;
        pthread_mutex_unlock(&lock);

         usleep((rand() % 1500) * 1000);  // de 0 a 1500 ms
    }

    pthread_exit(0); //return NULL
}

void *rotina_f2(void *p_param)
{
    int *valor = (int *)p_param;

    for(int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&lock);
        int tmp = *valor;
        tmp++;
        printf("f2 id : %lu, valor %d\n\n", pthread_self(), *valor);

        *valor = tmp;
        pthread_mutex_unlock(&lock);

         usleep((rand() % 1500) * 1000);  // de 0 a 1500 ms
    }

    pthread_exit(0); //return NULL
}

int main(void)
{
    printf("INICIO ...... \n\n");
    int valor = 0;

    srand(time(NULL));

    pthread_create(&rotina[0], NULL, rotina_f1, &valor);
    pthread_create(&rotina[1], NULL, rotina_f2, &valor);

    pthread_join(rotina[0], NULL);
    pthread_join(rotina[1], NULL);

    printf("valor final %d\n\n", valor );
    printf("ENCERRADO. \n\n");

    pthread_mutex_destroy(&lock);

    return 0;
}
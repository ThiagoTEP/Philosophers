#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_t rotina[2];

struct dados_f2 {
    char texto[20];
    float valor;
};

void *rotina_f1(void *p_param)
{
    int x = *((int *) p_param);

    printf("parametro : %d\n", x);

    for(int i = x; i < 5; ++i)
    {
        printf("numero %d id thread: %lu\n", i , (unsigned long)pthread_self());

        for(int j = 0; j < 1000000000; j++) { }
    }  
    return NULL; 
}

void *rotina_f2(void *p_param)
{
    struct dados_f2 *f2 = (struct dados_f2 *)p_param;

    for(int i = 0; i < 5; ++i)
    {
        printf("texto: %s, valor: %f, id thread: %lu\n",
               f2->texto, f2->valor, (unsigned long)pthread_self());

        for(int j = 0; j < 2000000000; j++) { }
    }
    return NULL; 
}

int main()
{
    printf("INICIO THREAD....\n\n");
    
    int parametro = 1;
    struct dados_f2 f2 = {"teste", 1.23};

    pthread_create(&rotina[0], NULL, rotina_f1, &parametro);
    pthread_create(&rotina[1], NULL, rotina_f2, &f2);

    printf("id da thread 1: %lu\n", (unsigned long)rotina[0]);
    printf("id da thread 2: %lu\n", (unsigned long)rotina[1]);

    pthread_join(rotina[0], NULL);
    pthread_join(rotina[1], NULL);

    return 0;
}

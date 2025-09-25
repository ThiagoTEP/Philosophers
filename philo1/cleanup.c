#include "philo.h"

void cleanup(t_data *data)
{
    for (int i = 0; i < data->num_philos; i++)
        pthread_mutex_destroy(&data->forks[i]);
    pthread_mutex_destroy(&data->write_mutex);

    free(data->forks);
    free(data->philos);
}

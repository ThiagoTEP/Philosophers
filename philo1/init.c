#include "philo.h"

int init_data(t_data *data, int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        return (1);
    data->num_philos = atoi(argv[1]);
    data->time_to_die = atol(argv[2]);
    data->time_to_eat = atol(argv[3]);
    data->time_to_sleep = atol(argv[4]);
    data->meals_required = (argc == 6) ? atoi(argv[5]) : -1;
    data->stop = 0;
    data->start_time = get_time();
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    data->philos = malloc(sizeof(t_philo) * data->num_philos);
    if (!data->forks || !data->philos)
        return (1);
    for (int i = 0; i < data->num_philos; i++)
        pthread_mutex_init(&data->forks[i], NULL);
    pthread_mutex_init(&data->write_mutex, NULL);
    return (0);
}

int init_philos(t_data *data)
{
    for (int i = 0; i < data->num_philos; i++)
    {
        data->philos[i].id = i + 1;
        data->philos[i].meals = 0;
        data->philos[i].last_meal = get_time();
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
        data->philos[i].data = data;
    }
    return (0);
}


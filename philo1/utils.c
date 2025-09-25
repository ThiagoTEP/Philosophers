#include "philo.h"

long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_usleep(long ms)
{
    long start = get_time();
    while ((get_time() - start) < ms)
        usleep(100);
}

void print_action(t_philo *philo, char *action)
{
    pthread_mutex_lock(&philo->data->write_mutex);
    if (!philo->data->stop)
        printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id, action);
    pthread_mutex_unlock(&philo->data->write_mutex);
}


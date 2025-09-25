#include "philo.h"

void take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_action(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_action(philo, "has taken a fork");
}

void drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    while (!philo->data->stop)
    {
        take_forks(philo);
        philo->last_meal = get_time();
        print_action(philo, "is eating");
        ft_usleep(philo->data->time_to_eat);
        philo->meals++;
        drop_forks(philo);
        print_action(philo, "is sleeping");
        ft_usleep(philo->data->time_to_sleep);
        print_action(philo, "is thinking");
        if (philo->data->meals_required != -1 &&
            philo->meals >= philo->data->meals_required)
            break;
    }
    return (NULL);
}

int start_threads(t_data *data)
{
    pthread_t monitor;
    for (int i = 0; i < data->num_philos; i++)
        if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]))
            return (1);
    pthread_create(&monitor, NULL, monitor_routine, data);
    for (int i = 0; i < data->num_philos; i++)
        pthread_join(data->philos[i].thread, NULL);
    pthread_join(monitor, NULL);
    return (0);
}




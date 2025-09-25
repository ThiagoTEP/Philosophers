#include "philosophers.h"

int emulation_stop(t_data *vars)
{
    int stop;
    pthread_mutex_lock(&vars->stop_mutex);
    stop = vars->stop;
    pthread_mutex_unlock(&vars->stop_mutex);
    return stop;
}

void print_action(t_philo *philo, char *action)
{
    if (!emulation_stop(philo->vars))
    {
        pthread_mutex_lock(&philo->vars->print_mutex);
        long time = get_time() - philo->vars->start_time;
        printf("%ld %d %s\n", time, philo->id, action);
        pthread_mutex_unlock(&philo->vars->print_mutex);
    }
}

static void take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_action(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken a fork");
    }
}

static void philo_routine_do(t_philo *philo)
{
    if (philo->id % 2 == 0)
        ft_usleep(5);

    while (!emulation_stop(philo->vars))
    {
        take_forks(philo);

        pthread_mutex_lock(&philo->meal_mutex);
        philo->last_meal_time = get_time();
        philo->meals_eaten++;
        print_action(philo, "is eating");
        pthread_mutex_unlock(&philo->meal_mutex);

        ft_usleep(philo->vars->time_to_eat);

        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

        print_action(philo, "is sleeping");
        ft_usleep(philo->vars->time_to_sleep);

        print_action(philo, "is thinking");
    }
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->vars->n_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        philo->last_meal_time = get_time();
        print_action(philo, "has taken a fork");
        ft_usleep(philo->vars->time_to_die);
        pthread_mutex_unlock(philo->left_fork);
        return NULL;
    }

    philo_routine_do(philo);
    return NULL;
}

static int all_ate_enough(t_data *vars)
{
    if (vars->n_eat < 0)
        return 0;

    int i = 0;
    while (i < vars->n_philos)
    {
        pthread_mutex_lock(&vars->philos[i].meal_mutex);
        if (vars->philos[i].meals_eaten < vars->n_eat)
        {
            pthread_mutex_unlock(&vars->philos[i].meal_mutex);
            return 0;
        }
        pthread_mutex_unlock(&vars->philos[i].meal_mutex);
        i++;
    }
    return 1;
}

void *monitor_philos(void *arg)
{
    t_data *vars = (t_data *)arg;
    int i;

    while (!emulation_stop(vars))
    {
        i = 0;
        while (i < vars->n_philos)
        {
            pthread_mutex_lock(&vars->philos[i].meal_mutex);
            if (get_time() - vars->philos[i].last_meal_time > vars->time_to_die)
            {
                pthread_mutex_unlock(&vars->philos[i].meal_mutex);

                pthread_mutex_lock(&vars->print_mutex);
                printf("%ld %d died\n", get_time() - vars->start_time, vars->philos[i].id);
                pthread_mutex_unlock(&vars->print_mutex);

                pthread_mutex_lock(&vars->stop_mutex);
                vars->stop = 1;
                pthread_mutex_unlock(&vars->stop_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&vars->philos[i].meal_mutex);
            i++;
        }

        if (all_ate_enough(vars))
        {
            pthread_mutex_lock(&vars->stop_mutex);
            vars->stop = 1;
            pthread_mutex_unlock(&vars->stop_mutex);
            return NULL;
        }

        usleep(100); // monitor mais frequente para precisão <10ms
    }
    return NULL;
}

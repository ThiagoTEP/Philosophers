#include "philo.h"

void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int finished;

    while (!data->stop)
    {
        finished = 0;
        for (int i = 0; i < data->num_philos; i++)
        {
            long diff = get_time() - data->philos[i].last_meal;
            if (diff > data->time_to_die)
            {
                print_action(&data->philos[i], "died");
                data->stop = 1;
                return (NULL);
            }
            if (data->meals_required != -1 && data->philos[i].meals >= data->meals_required)
                finished++;
        }
        if (data->meals_required != -1 && finished == data->num_philos)
        {
            data->stop = 1;
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}

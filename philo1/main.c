#include "philo.h"

int main(int argc, char **argv)
{
    t_data data;

    if (init_data(&data, argc, argv))
        return (1);
    init_philos(&data);
    if (start_threads(&data))
    {
        cleanup(&data);
        return (1);
    }
    cleanup(&data);
    return (0);
}

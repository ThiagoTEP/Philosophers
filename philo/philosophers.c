#include "philosophers.h"

int	emulation_stop(t_data *vars)
{
	int	stop;

	pthread_mutex_lock(&vars->stop_mutex);
	stop = vars->stop;
	pthread_mutex_unlock(&vars->stop_mutex);
	return (stop);
}

void	print_action(t_philo *philo, char *action)
{
	long	timestamp;

	pthread_mutex_lock(&philo->vars->print_mutex);
	if (!emulation_stop(philo->vars))
	{
		timestamp = get_time() - philo->vars->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, action);
	}
	pthread_mutex_unlock(&philo->vars->print_mutex);
}

int	set_args(t_data	*vars, char *av[], int ac)
{
	vars->n_philos = ft_atoi(av[1]);
	if (vars->n_philos < 1)
	{
		ft_putstr_error("Error\nNumber philo < 1");
		return (1);
	}
	vars->time_to_die = ft_atoi(av[2]);
	vars->time_to_eat = ft_atoi(av[3]);
	vars->time_to_sleep = ft_atoi(av[4]);
	vars->n_eat = -1;
	vars->stop = 0;
	if (ac == 6)
		vars->n_eat = ft_atoi(av[5]);
	return (0);
}

int	args_check(char *av[])
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (ft_strlen(av[i]) == 0)
			return (1);
		while (av[i][j])
		{
			if (av[i][j] >= '0' && av[i][j] <= '9')
				j++;
			else
			{
				ft_putstr_error("Error\ninvalid character");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_data		vars;
	pthread_t	monitor_thread;

	if (ac < 5 || ac > 6)
	{
		ft_putstr_error("Error\ninvalid number of arguments");
		return (1);
	}
	if (args_check(av) == 1 || set_args(&vars, av, ac) == 1)
		return (1);
	vars.start_time = get_time();
	if (init_forks(&vars) == 1)
		return (1);
	if (init_philos(&vars) == 1)
		return (1);
	if (init_threads(&vars) == 1)
		return (1);
	if (pthread_create(&monitor_thread, NULL, &monitor_philos, &vars) != 0)
		return (1);
	pthread_join(monitor_thread, NULL);
	ft_closed(&vars);
	return (0);
}
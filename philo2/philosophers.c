/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:45:27 by thevaris          #+#    #+#             */
/*   Updated: 2025/09/26 12:46:24 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	long	time;

	time = 0;
	if (!emulation_stop(philo->vars))
	{
		pthread_mutex_lock(&philo->vars->print_mutex);
		time = get_time() - philo->vars->start_time;
		printf("%ld %d %s\n", time, philo->id, action);
		pthread_mutex_unlock(&philo->vars->print_mutex);
	}
}

static int	set_args(t_data *vars, char *av[], int ac)
{
	vars->n_philos = ft_atoi(av[1]);
	vars->time_to_die = ft_atoi(av[2]);
	vars->time_to_eat = ft_atoi(av[3]);
	vars->time_to_sleep = ft_atoi(av[4]);
	vars->n_eat = -1;
	vars->stop = 0;
	if (ac == 6)
		vars->n_eat = ft_atoi(av[5]);
	return (0);
}

static int	args_check(char *av[], int ac)
{
	int	i;
	int	j;
	int	val;

	if (ac < 5 || ac > 6)
		return (1);
	i = 1;
	while (i < ac)
	{
		if (ft_strlen(av[i]) == 0)
			return (1);
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		val = ft_atoi(av[i]);
		if ((i == 1 || i == 2 || i == 3 || i == 4) && val < 1)
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_data		vars;
	pthread_t	monitor;

	if (args_check(av, ac))
		return (ft_putstr_error("Error\nInvalid arguments"), 1);
	set_args(&vars, av, ac);
	vars.start_time = get_time();
	if (init_forks(&vars) == 1)
		return (1);
	if (init_philos(&vars) == 1)
		return (ft_closed(&vars), 1);
	if (init_threads(&vars) == 1)
		return (ft_closed(&vars), 1);
	if (pthread_create(&monitor, NULL, &monitor_philos, &vars) != 0)
	{
		ft_closed(&vars);
		return (1);
	}
	pthread_join(monitor, NULL);
	ft_closed(&vars);
	return (0);
}

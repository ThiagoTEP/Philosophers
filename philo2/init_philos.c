/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:45:02 by thevaris          #+#    #+#             */
/*   Updated: 2025/09/26 12:49:45 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_forks(t_data *vars)
{
	int	i;

	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->n_philos);
	if (!vars->forks)
		return (1);
	i = 0;
	while (i < vars->n_philos)
	{
		if (pthread_mutex_init(&vars->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&vars->forks[i]);
			free(vars->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philos(t_data *vars)
{
	int	i;

	vars->philos = malloc(sizeof(t_philo) * vars->n_philos);
	if (!vars->philos)
	{
		free(vars->forks);
		return (1);
	}
	i = 0;
	while (i < vars->n_philos)
	{
		vars->philos[i].id = i + 1;
		vars->philos[i].meals_eaten = 0;
		vars->philos[i].last_meal_time = get_time();
		vars->philos[i].vars = vars;
		pthread_mutex_init(&vars->philos[i].meal_mutex, NULL);
		vars->philos[i].left_fork = &vars->forks[i];
		vars->philos[i].right_fork = &vars->forks[(i + 1) % vars->n_philos];
		i++;
	}
	return (0);
}

int	init_threads(t_data *vars)
{
	int	i;

	pthread_mutex_init(&vars->print_mutex, NULL);
	pthread_mutex_init(&vars->stop_mutex, NULL);
	i = 0;
	while (i < vars->n_philos)
	{
		if (pthread_create(&vars->philos[i].thread, NULL,
				&philo_routine, &vars->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_closed(t_data *vars)
{
	int	i;

	if (!vars->philos || !vars->forks)
		return ;
	i = 0;
	while (i < vars->n_philos)
		pthread_join(vars->philos[i++].thread, NULL);
	i = 0;
	while (i < vars->n_philos)
		pthread_mutex_destroy(&vars->forks[i++]);
	pthread_mutex_destroy(&vars->print_mutex);
	pthread_mutex_destroy(&vars->stop_mutex);
	i = 0;
	while (i < vars->n_philos)
		pthread_mutex_destroy(&vars->philos[i++].meal_mutex);
	free(vars->philos);
	free(vars->forks);
}

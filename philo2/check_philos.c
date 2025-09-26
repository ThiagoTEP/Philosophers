/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:53:14 by thevaris          #+#    #+#             */
/*   Updated: 2025/09/26 12:53:17 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_data *vars, int i)
{
	pthread_mutex_lock(&vars->philos[i].meal_mutex);
	if (get_time() - vars->philos[i].last_meal_time > vars->time_to_die)
	{
		pthread_mutex_unlock(&vars->philos[i].meal_mutex);
		pthread_mutex_lock(&vars->print_mutex);
		printf("%ld %d died\n", get_time() - vars->start_time,
			vars->philos[i].id);
		pthread_mutex_unlock(&vars->print_mutex);
		pthread_mutex_lock(&vars->stop_mutex);
		vars->stop = 1;
		pthread_mutex_unlock(&vars->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&vars->philos[i].meal_mutex);
	return (0);
}

int	all_ate_enough(t_data *vars)
{
	int	i;

	if (vars->n_eat < 0)
		return (0);
	i = 0;
	while (i < vars->n_philos)
	{
		pthread_mutex_lock(&vars->philos[i].meal_mutex);
		if (vars->philos[i].meals_eaten < vars->n_eat)
		{
			pthread_mutex_unlock(&vars->philos[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&vars->philos[i].meal_mutex);
		i++;
	}
	return (1);
}

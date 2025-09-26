/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:45:33 by thevaris          #+#    #+#             */
/*   Updated: 2025/09/26 12:54:11 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_philo *philo)
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

static void	philo_routine_do(t_philo *philo)
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

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->vars->n_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		philo->last_meal_time = get_time();
		print_action(philo, "has taken a fork");
		ft_usleep(philo->vars->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	philo_routine_do(philo);
	return (NULL);
}

void	*monitor_philos(void *arg)
{
	t_data	*vars;
	int		i;

	vars = (t_data *)arg;
	while (!emulation_stop(vars))
	{
		i = 0;
		while (i < vars->n_philos)
		{
			if (check_death(vars, i))
				return (NULL);
			i++;
		}
		if (all_ate_enough(vars))
		{
			pthread_mutex_lock(&vars->stop_mutex);
			vars->stop = 1;
			pthread_mutex_unlock(&vars->stop_mutex);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

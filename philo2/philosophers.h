/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:45:46 by thevaris          #+#    #+#             */
/*   Updated: 2025/09/26 12:53:43 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*vars;
}	t_philo;

typedef struct s_data
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_eat;
	long			start_time;
	int				stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	t_philo			*philos;
}	t_data;

/* utils */
long	get_time(void);
void	ft_usleep(long time_in_ms);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
void	ft_putstr_error(char *str);

/* init */
int		init_forks(t_data *vars);
int		init_philos(t_data *vars);
int		init_threads(t_data *vars);
void	ft_closed(t_data *vars);

/* routine */
void	*philo_routine(void *arg);
void	*monitor_philos(void *arg);
int		emulation_stop(t_data *vars);
int		check_death(t_data *vars, int i);
int		all_ate_enough(t_data *vars);

/* actions */
void	print_action(t_philo *philo, char *action);

#endif

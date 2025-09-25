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
	pthread_t		philo;
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

void	ft_usleep(long time_in_ms);
long	get_time(void);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
int		init_forks(t_data *vars);
int		init_philos(t_data *vars);
int		init_threads(t_data *vars);
void	*philo_routine(void	*arg);
void	print_action(t_philo *philo, char *action);
int		emulation_stop(t_data *vars);
void	*monitor_philos(void *arg);
void	ft_closed(t_data *vars);
void	ft_putstr_error(char *str);

#endif
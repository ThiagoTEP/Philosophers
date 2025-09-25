#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data t_data;

typedef struct s_philo
{
    int id;
    int meals;
    long last_meal;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data *data;
} t_philo;

struct s_data
{
    int num_philos;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int meals_required;
    int stop;
    long start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t write_mutex;
    t_philo *philos;
};

// utils.c
long get_time(void);
void ft_usleep(long ms);
void print_action(t_philo *philo, char *action);

// init.c
int init_data(t_data *data, int argc, char **argv);
int init_philos(t_data *data);

// routine.c
void *philo_routine(void *arg);
void take_forks(t_philo *philo);
void drop_forks(t_philo *philo);
int start_threads(t_data *data);

// monitor.c
void *monitor_routine(void *arg);

// cleanup.c
void cleanup(t_data *data);

#endif

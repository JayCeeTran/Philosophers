#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_data{
	int philos;
	int ms_die;
	int ms_eat;
	int ms_sleep;
	int must_eat;
	_Atomic int dead;
	pthread_mutex_t *forks;
} t_data;

typedef struct s_phil{
	int id;
	long last_meal_time;
	int meals;
	pthread_t thread;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	t_data *data;
} t_phil;


int	ft_atoi(const char *str);
int	save_arguments_in_struct(t_data *data, char **av);
int		initialize_phils(t_data *data);
void	destroy_mutexes(int i, pthread_mutex_t *forks);
void	*routine(void *arg);
int create_thread(t_phil *phils);
/**
***		LOG FUNCTIONS
**/
long    get_time(void);
void    picking_forks(t_phil *phils);
void    eating(t_phil *phils);
void    thinking(t_phil *phils);
void    sleeping(t_phil *phils);
void    *check_dead(t_phil *phils);
void    dead(t_phil *phils, long otime);
/**
***		ERROR MSGS!!!
**/
void	failed_malloc(void);
void	too_few_arguments(void);
void	invalid_argument(void);
void	mutex_init_failed(t_phil *phils);

#endif

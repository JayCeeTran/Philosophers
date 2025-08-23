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
//	int *queue;
	_Atomic int created;
	_Atomic int who_running;
	_Atomic int rounds;
	_Atomic int phils_eaten;
	_Atomic int dead;
	_Atomic int start;
	_Atomic	long start_time;
	pthread_mutex_t *print;
	pthread_mutex_t *forks;
} t_data;

typedef struct s_phil{
	int id;
	long last_meal_time;
	int meals;
	int round;
	pthread_t thread;
	pthread_mutex_t *print;
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
//void	rotate_queue(t_data *data);
void	unlock(t_phil *phils);
/**
***		LOG FUNCTIONS
**/
long    get_time(long start_time);
long	get_start_time(void);
int	picking_forks(t_phil *phils, long start_time);
int    eating(t_phil *phils, int duration);
void    thinking(t_phil *phils);
int    sleeping(t_phil *phils, int duration);
int     check_dead(t_phil *phils);
int   dead(t_phil *phils, long otime);
/**
***		ERROR MSGS!!!
**/
void	failed_malloc(void);
void	too_few_arguments(void);
void	invalid_argument(void);
void	mutex_init_failed(t_phil *phils);

#endif

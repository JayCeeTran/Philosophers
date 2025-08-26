/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:36:15 by jtran             #+#    #+#             */
/*   Updated: 2025/08/25 13:38:58 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				philos;
	int				ms_die;
	int				ms_eat;
	int				ms_sleep;
	int				must_eat;
	_Atomic int		created;
	_Atomic int		rounds;
	_Atomic int		dead;
	_Atomic int		start;
	_Atomic long	start_time;
	pthread_mutex_t	*print;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_phil
{
	int				id;
	_Atomic long	last_meal_time;
	_Atomic int		meals;
	pthread_t		thread;
	pthread_mutex_t	*print;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_data			*data;
}					t_phil;

void				atoi_arguments(t_data *data, char **av);
void				*phil_1_die(t_phil *phil);
void				print_mutex(t_phil *phils, long time, char *s);
int					ft_atoi(const char *str);
int					save_arguments_in_struct(t_data *data, char **av);
int					initialize_phils(t_data *data);
void				destroy_mutexes(int i, pthread_mutex_t *forks);
void				*routine(void *arg);
int					create_thread(t_phil *phils, int i);
void				unlock(t_phil *phils);
void				destroy_and_free(t_phil *phils, t_data *data, int i);
/**
***		LOG FUNCTIONS
**/
long				get_time(long start_time);
long				get_start_time(void);
int					picking_forks(t_phil *phil, long start_time);
int					eating(t_phil *phil, int duration);
void				thinking(t_phil *phil);
int					sleeping(t_phil *phil, int duration);

/**
***		ERROR MSGS!!!
**/
void				failed_malloc(void);
void				too_few_arguments(void);
void				invalid_argument(void);
void				mutex_init_failed(t_phil *phils);

#endif

#include "philo.h"

long	get_time(long start_time)
{
	struct timeval tv;
	long result;

	gettimeofday(&tv, NULL);
	result = tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time;
	return(result);
}

long	get_start_time(void)
{
	struct timeval tv;
	long result;

	gettimeofday(&tv, NULL);
	result = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return(result);
}

void	phil_1_die(t_phil *phil)
{
	pthread_mutex_lock(phil->left);
	print_mutex(phil, get_time(phil->data->start_time), "has taken a fork");			
	while(!phil->data->dead)
		usleep(500);
	pthread_mutex_unlock(phil->left);
}

int	picking_forks(t_phil *phil, long start_time)
{
	int quit;

	quit = 0;
	if(phil->id % 2 == 1)
	{
		pthread_mutex_lock(phil->right);
		print_mutex(phil, get_time(start_time), "has taken a fork");	
		pthread_mutex_lock(phil->left);
		print_mutex(phil, get_time(start_time), "has taken a fork");	
	}
	else if(phil->id % 2 == 0)
	{
		pthread_mutex_lock(phil->left);
		print_mutex(phil, get_time(start_time), "has taken a fork");	
		pthread_mutex_lock(phil->right);
		print_mutex(phil, get_time(start_time), "has taken a fork");	
	}
	quit = eating(phil, phil->data->ms_eat);
	unlock(phil);
	if(!quit)
		return(0);
	return(1);
}

int	eating(t_phil *phil, int duration)
{
	phil->meals++;
	phil->last_meal_time = get_time(phil->data->start_time);
	print_mutex(phil, phil->last_meal_time, "is eating");
	while(get_time(phil->data->start_time) - phil->last_meal_time < duration && !phil->data->dead)	
		usleep(500);
	return(1);
}

void	thinking(t_phil *phil)
{
	long time;

	time = get_time(phil->data->start_time);
	print_mutex(phil, time, "is thinking");
}

int	sleeping(t_phil *phil, int duration)
{
	long time;

	time = get_time(phil->data->start_time);
	print_mutex(phil, time, "is sleeping");
	while(get_time(phil->data->start_time) - time < duration && !phil->data->dead)
		usleep(500);
	return(1);
}

#include "philo.h"

int	picking_forks(t_phil *phil, long start_time)
{
	int quit;

	quit = 0;
	if(phil->data->dead)
		return(0);
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
	if(quit)
		return(0);
	return(1);
}

int	eating(t_phil *phil, int duration)
{
	t_data *data;
	long time;

	data = phil->data;
	phil->meals++;
	time = get_time(data->start_time);
	if(time - phil->last_meal_time >= data->ms_die)
	{
		data->dead = 1;
		return(1);
	}
	phil->last_meal_time = time;
	print_mutex(phil, phil->last_meal_time, "is eating");
	while(!data->dead && get_time(data->start_time) - time < duration)	
		usleep(500);
	if(data->dead)
		return(1);
	return(0);
}

void	thinking(t_phil *phil)
{
	long time;

	time = get_time(phil->data->start_time);
	print_mutex(phil, time, "is thinking");
}

int	sleeping(t_phil *phil, int duration)
{
	t_data *data;
	long time;

	data = phil->data;
	time = get_time(data->start_time);
	print_mutex(phil, time, "is sleeping");
	while(!data->dead && get_time(data->start_time) - time < duration)
		usleep(500);
	if(data->dead)
		return(0);
	return(1);
}

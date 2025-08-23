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

void	phil_1_die(t_phil *phils)
{
	long time;

	time = 0;
	while(time <= phils->data->ms_die)
	{
		time = get_time(phils->data->start_time);
		usleep(10);
	}
	printf("%ld 1 died\n", time);
	phils->data->dead = 1;
}

int	picking_forks(t_phil *phils, long start_time)
{
	long time;
	int quit;

	quit = 0;
	time = get_time(start_time);
	if(phils->id % 2 == 1)
	{	
		pthread_mutex_lock(phils->left);
		printf("%ld %d has taken a fork\n", time, phils->id); //get time on everything?
		if(!phils->right)
		{
			phil_1_die(phils);
			return(0);
		}
		pthread_mutex_lock(phils->right);
		printf("%ld %d has taken a fork\n", time, phils->id);
	}
	else if(phils->id % 2 == 0)
	{
		pthread_mutex_lock(phils->right);
		printf("%ld %d has taken a fork\n", time, phils->id);
		pthread_mutex_lock(phils->left);
		printf("%ld %d has taken a fork\n", time, phils->id);
	}
	if(!check_dead(phils))
	{
		unlock(phils);
		return (0);
	}
	if(dead(phils, start_time))
		return(0);
	quit = eating(phils, phils->data->ms_eat);
	unlock(phils);
	if(!quit)
		return(0);
	return(1);
}

int	eating(t_phil *phils, int duration)
{
	phils->meals++;
	phils->last_meal_time = get_time(phils->data->start_time);
	printf("%ld %d is eating\n", phils->last_meal_time, phils->id);
	while(get_time(phils->data->start_time) - phils->last_meal_time < duration)
	{	
		usleep(100);
		if(!check_dead(phils))
			return (0);
	}
	return(1);
}

void	thinking(t_phil *phils)
{
	long time;

	time = get_time(phils->data->start_time);
	printf("%ld %d is thinking\n", time, phils->id);
}

int	sleeping(t_phil *phils, int duration)
{
	long time;

	time = get_time(phils->data->start_time);
	printf("%ld %d is sleeping\n", time, phils->id);
	while(get_time(phils->data->start_time) - time < duration)
	{
		usleep(100);
		if(!check_dead(phils))
			return (0);
	}
	return(1);
}

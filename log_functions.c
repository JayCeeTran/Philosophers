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
	printf("Philosopher 1 died. Time of death %ld\n", time);
	phils->data->dead = 1;
}

int	picking_forks(t_phil *phils, long start_time)
{
	long time;

	time = get_time(start_time);
	if(!check_dead(phils))
	{
			return (0);;
	}
	if(phils->id % 2 == 1)
	{	
		pthread_mutex_lock(phils->left);
		printf("%ld Philosopher:%d picked up left fork\n", time, phils->id); //get time on everything?
		if(!phils->right)
		{
			phil_1_die(phils);
			return(0);
		}
		pthread_mutex_lock(phils->right);
		printf("%ld Philosopher:%d picked up right fork\n", time, phils->id);
	}
	else if(phils->id % 2 == 0)
	{
		pthread_mutex_lock(phils->right);
		printf("%ld Philosopher:%d picked up right fork\n", time, phils->id);
		pthread_mutex_lock(phils->left);
		printf("%ld Philosopher:%d picked up left fork\n", time, phils->id);
	}
	if(!check_dead(phils))
	{
		unlock(phils);
		return (0);
	}
	pthread_mutex_lock(phils->print);
	dead(phils, start_time);
	pthread_mutex_unlock(phils->print);
	if(!check_dead(phils))
	{
		unlock(phils);	
		return (0);
	}
	eating(phils);
	unlock(phils);
	return(1);
}

void	eating(t_phil *phils)
{
	phils->meals++;
	phils->last_meal_time = get_time(phils->data->start_time);
	printf("%ld Philosopher:%d is eating\n", phils->last_meal_time, phils->id);
	usleep(phils->data->ms_eat * 1000);
}

void	thinking(t_phil *phils)
{
	long time;

	time = get_time(phils->data->start_time);
	printf("%ld Philosopher:%d is thinking\n", time, phils->id);
	//usleep(10);
}

void	sleeping(t_phil *phils)
{
	long time;

	time = get_time(phils->data->start_time);
	printf("%ld Philosopher:%d is sleeping\n", time, phils->id);
	usleep(phils->data->ms_sleep);
}

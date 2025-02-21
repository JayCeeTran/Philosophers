#include "philo.h"

long	get_time(void)
{
	struct timeval tv;
	long result;

	gettimeofday(&tv, NULL);
	result = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return(result);
}

void	picking_forks(t_phil *phils)
{
	long time;

	time = get_time();
	if(phils->id % 2 == 1)
	{	
		pthread_mutex_lock(phils->left);
		printf("%ld Philosopher:%d picked up left fork\n", time, phils->id);
		pthread_mutex_lock(phils->right);
		printf("%ld Philosopher:%d picked up right fork\n", get_time(), phils->id);
	}
	else if(phils->id % 2 == 0)
	{
		pthread_mutex_lock(phils->right);
		printf("%ld Philosopher:%d picked up right fork\n", time, phils->id);
		pthread_mutex_lock(phils->left);
		printf("%ld Philosopher:%d picked up left fork\n", time, phils->id);
	}
	dead(phils, time);
	eating(phils);
	pthread_mutex_unlock(phils->left);
	pthread_mutex_unlock(phils->right);
}

void	eating(t_phil *phils)
{
	phils->meals++;
	phils->last_meal_time = get_time();
	printf("%ld Philosopher:%d is eating\n", phils->last_meal_time, phils->id);
	usleep(phils->data->ms_eat * 1000);
}

void	thinking(t_phil *phils)
{
	long time;

	time = get_time();
	printf("%ld Philosopher:%d is thinking\n", time, phils->id);
}

void	sleeping(t_phil *phils)
{
	long time;

	time = get_time();
	printf("%ld Philosopher:%d is sleeping\n", time, phils->id);
	usleep(phils->data->ms_sleep);
}

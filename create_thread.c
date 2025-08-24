#include "philo.h"

int	check_dead_phil(t_phil *phil, t_data *data, int i);
int     check_for_meals(t_phil *phil, t_data *data, int i);

int	stalk_phils(t_phil *phil)
{
	int i;
	int eaten;
	t_data *data;

	data = phil->data;
	while(data->dead == 0)
	{
		i = 0;
		eaten = 0;
		while(i < data->philos)
		{
			if(check_dead_phil(phil, data, i))
			{
				data->dead = 1;
				pthread_mutex_lock(phil->print);
				printf("%ld %d died\n", get_time(data->start_time), phil[i].id);
				pthread_mutex_unlock(phil->print);
				break;
			}
			if(data->must_eat > 0)
				eaten += check_for_meals(phil, data, i);
			if(eaten >= data->philos)
			{
				data->dead = 1;	
				return(1);
			}
			i++;
		}
		usleep(500);
	}
	return(1);
}

int	check_dead_phil(t_phil *phil, t_data *data, int i)
{
	if(get_time(data->start_time) - phil[i].last_meal_time > data->ms_die)
	{	
		data->dead = 1;
		return(1);
	}
	return(0);
}

int 	check_for_meals(t_phil *phil, t_data *data, int i)
{
	if(phil[i].meals >= data->must_eat)
		return(1);
	return(0);
}

int create_thread(t_phil *phils)
{
	int i;
	
	i = 0;
	while(i < phils->data->philos)
	{
		if(pthread_create(&phils[i].thread, NULL, routine, &phils[i]))
		{
			while(--i >= 0)
			{
				pthread_cancel(phils[i].thread);
				pthread_join(phils[i].thread, NULL);
			}
			destroy_mutexes(phils->data->philos, phils->data->forks);
			free(phils);
			write(2, "Error\nFailed to create threads\n", 31);
			return(0);
		}
		i++;
	}
	while(phils->data->created < phils->data->philos)
		usleep(500);
	phils->data->start_time = get_start_time();
	phils->data->start = 1;
	stalk_phils(phils);
	while(--i >= 0)
		pthread_join(phils[i].thread, NULL);
	return(1);
}

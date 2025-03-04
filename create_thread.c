#include "philo.h"

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
	while(--i >= 0)
		pthread_join(phils[i].thread, NULL);
	return(1);
}

void	*routine(void *arg)
{
	t_phil *phil;

	phil = (t_phil*)arg;
	while(phil->meals < phil->data->must_eat && phil->data->dead == 0)
	{
		picking_forks(phil);
		if(!check_dead(phil))
			break;
		sleeping(phil);
		if(!check_dead(phil))
			break;
		thinking(phil);
		if(!check_dead(phil))
			break;
	}
	return(NULL);
}

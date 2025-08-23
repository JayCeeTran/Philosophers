#include "philo.h"

/*void	create_queue(t_data *data)
{
	data->queue = malloc(sizeof(int) * 2);
	data->queue[0] = 1;
	data->queue[1] = data->philos;
}

void	swap_queue(t_data *data)
{
	int temp;

	temp = data->queue[0];
	data->queue[0] = data->queue[1];
	data->queue[1] = temp;
}*/

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
		usleep(10);
	phils->data->start_time = get_start_time();
	phils->data->start = 1;
	while(--i >= 0)
		pthread_join(phils[i].thread, NULL);
	return(1);
}

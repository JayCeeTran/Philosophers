#include "philo.h"

void	create_queue(t_data *data)
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
}

int create_thread(t_phil *phils)
{
	int i;
	
	i = 0;
	create_queue(phils->data);
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

void	*routine(void *arg)
{
	t_phil *phil;
	t_data *data;

	phil = (t_phil*)arg;
	data = phil->data;
	data->created++;
	while(data->start == 0)
		usleep(10);
	while((data->must_eat == -1 || phil->meals < data->must_eat) && data->dead == 0)
	{
		while(1)
		{
			if(phil->round < data->rounds && data->who_running == phil->id % 2)
			{
				if(phil->id == 1 || phil->id == data->philos)
				{
					while(phil->id != data->queue[0])
					{
						usleep(10);
						if(!check_dead(phil))
							return(NULL);
					}
				}
				if(!picking_forks(phil, data->start_time))
					return(NULL);
				if(phil->id == 1 || phil->id == data->philos)
					swap_queue(data);
				phil->round++;
				data->phils_eaten++;
				if(data->phils_eaten == (data->philos + data->who_running) / 2)
				{
					data->phils_eaten = 0;
					if(phil->id % 2 == 1)
						data->who_running = 0;
					else
					{
						data->who_running = 1;
						data->rounds++;
					}
				}
				usleep(10);
				break;
			}
			usleep(10);	
			if(!check_dead(phil))
				return(NULL);
		}
		if(!check_dead(phil))
			return(NULL);
		sleeping(phil);
		if(!check_dead(phil))
			return(NULL);
		thinking(phil);
		if(!check_dead(phil))
			return(NULL);
	}
	return(NULL);
}

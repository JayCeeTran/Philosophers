#include "philo.h"

void	round_1(t_phil *phil, t_data *data, long time)
{
	if(phil->id % 2 == 0)
	{
		if(data->philos % 2 == 1)
		{
			time = get_time(data->start_time);
			while(!data->dead && get_time(data->start_time) - time < data->ms_eat * 0.8 * 2)
				usleep(500);
		}
		else
		{
			time = get_time(data->start_time);
			while(!data->dead && get_time(data->start_time) - time < data->ms_eat * 0.75) 
				usleep(500);
		}
		data->rounds = 2;
	}
	if(phil->id == data->philos && data->philos % 2 == 1)
	{
		time = get_time(data->start_time);
		while(!data->dead && get_time(data->start_time) - time < data->ms_eat * 0.5) 
			usleep(500);
	}
}

void	other_rounds(t_data *data, long time, long think_time)
{
	time = get_time(data->start_time);
	think_time = data->ms_die - data->ms_eat - data->ms_sleep;
	if(think_time > 50)
	{
		while(!data->dead && get_time(data->start_time) - time < think_time * 0.75)
			usleep(500);
	}
}

void	*routine(void *arg)
{
	t_phil *phil;
	t_data *data;

	phil = (t_phil*)arg;
	data = phil->data;
	data->created++;
	while(!data->dead && data->start == 0)
		usleep(500);
	if(!data->dead && data->philos == 1)
		return(phil_1_die(phil));
	while(!data->dead)
	{
		if(data->dead)
			return(NULL);
		thinking(phil);
		if(data->rounds == 1)
			round_1(phil, data, 0);
		else if(data->philos % 2 == 1)
			other_rounds(data, 0, 0);
		if(!picking_forks(phil, data->start_time))
			return(NULL);
		if(!sleeping(phil, data->ms_sleep))
			return(NULL);
	}
	return(NULL);
}

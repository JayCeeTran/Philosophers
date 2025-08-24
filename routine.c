#include "philo.h"

void	*routine(void *arg)
{
	t_phil *phil;
	t_data *data;
	int time;
	long	think_time;

	phil = (t_phil*)arg;
	data = phil->data;
	data->created++;
	while(data->start == 0)
		usleep(500);
	if(data->philos == 1)
	{
		phil_1_die(phil);
		return(NULL);
	}
	while(data->dead == 0)
	{
		if(check_dead(phil))
			return(NULL);
		thinking(phil);
		if(data->rounds == 1)
		{
			if(phil->id % 2 == 0)
			{
				if(data->philos % 2 == 1)
				{
					time = get_time(data->start_time);
					while(get_time(data->start_time) - time < data->ms_eat * 0.75 * 2)
					{
						if(check_dead(phil))
							return(NULL);
						usleep(100);
					}
				}
				else
				{
					time = get_time(data->start_time);
					while(get_time(data->start_time) - time < data->ms_eat * 0.65) 
					{	
						if(check_dead(phil))
							return(NULL);
						usleep(100);
					}
				}
				data->rounds = 2;
			}
			if(phil->id == data->philos && data->philos % 2 == 1)
			{
				time = get_time(data->start_time);
				while(get_time(data->start_time) - time < data->ms_eat * 0.5) 
				{
					if(check_dead(phil))
							return(NULL);
					usleep(100);
				}
			}
		}
		else if(data->philos % 2 == 1)
		{
			time = get_time(data->start_time);
			think_time = data->ms_die - data->ms_eat - data->ms_sleep;
			if(think_time > 50)
			{
				while(get_time(data->start_time) - time < think_time * 0.75)
				{
					usleep(100);
					if(check_dead(phil))
						return(NULL);
				}
			}
		}
		if(!picking_forks(phil, data->start_time))
			return(NULL);
		phil->round++;
		if(!sleeping(phil, data->ms_sleep))
			return(NULL);
	}
	return(NULL);
}

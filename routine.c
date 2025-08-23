#include "philo.h"

void	*routine(void *arg)
{
	t_phil *phil;
	t_data *data;
	int time;

	phil = (t_phil*)arg;
	data = phil->data;
	data->created++;
	while(data->start == 0)
		usleep(10);
	while((data->must_eat == -1 || phil->meals < data->must_eat) && data->dead == 0)
	{
		if(data->rounds == 1 && phil->id % 2 == 0)
		{
			if(data->philos % 2 == 1)
			{
				usleep(data->ms_eat * 1000 * 2);
			}
			else
			{
				usleep(data->ms_eat * 1000);
			}
			data->rounds++;
		}
		if(data->rounds == 1 && phil->id == data->philos && data->philos % 2 == 1)
		{
			usleep(data->ms_eat * 1000);
		}
		thinking(phil);
		if(!check_dead(phil))
			return(NULL);
		if(!picking_forks(phil, data->start_time))
			return(NULL);
		phil->round++;
		if(!sleeping(phil, data->ms_sleep))
			return(NULL);
		if(data->philos % 2 == 1)
		{
			time = get_time(data->start_time);
			while(get_time(data->start_time) - time < data->ms_eat)
			{
				usleep(100);
				if(!check_dead(phil))
					return(NULL);
			}
		}
	}
	return(NULL);
}

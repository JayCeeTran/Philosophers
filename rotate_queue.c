#include "philo.h"

void rotate_queue(t_data *data)
{
	int i;
	int temp;

	i = 0;
	temp = data->queue[0];
	while(i < data->philos - 1)
	{
		data->queue[i] = data->queue[i + 1];
		i++;
	}
	data->queue[data->philos - 1] = temp;
}

#include "philo.h"

static int   fill_phils(t_phil *phils, t_data *data, int i, int j);


int initialize_phils(t_data *data)
{
	t_phil *phils;

	phils = malloc(data->philos * sizeof(t_phil));
	if(!phils)
	{
		failed_malloc();
		return(0);
	}
	if(!fill_phils(phils, data, 0, 0))
		return(0);
	if(!create_thread(phils))
		return(0);
	free(phils);
	free(data->queue);
	return(1);
}

static int	fill_phils(t_phil *phils, t_data *data, int i, int j)
{
	data->forks = malloc(data->philos * sizeof(pthread_mutex_t));
	data->print = malloc(sizeof(pthread_mutex_t));
	if(pthread_mutex_init(data->print, NULL))
		return(0);
	while(j < data->philos)
	{
		if(pthread_mutex_init(&data->forks[j], NULL))
		{
			destroy_mutexes(j, data->forks);
			mutex_init_failed(phils);
			free(phils);
			return(0);
		}
		j++;
	}
	while(i < data->philos)
	{
		phils[i].id = i + 1;
		phils[i].last_meal_time = 0;
		phils[i].meals = 0;
		phils[i].round = 0;
		phils[i].data = data;
		phils[i].left = &data->forks[i];
		phils[i].print = data->print;
		if(data->philos == 1)
		{
			phils[i].right = NULL;
			break;
		}
		phils[i].right = &data->forks[(i + 1) % data->philos];
		i++;
	}
	return(1);
}

void    destroy_mutexes(int i, pthread_mutex_t *forks)
{
    while(--i >= 0)
    {
        pthread_mutex_destroy(&forks[i]);
    }
    free(forks);
}       

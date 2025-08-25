#include "philo.h"

void unlock(t_phil *phils)
{
	pthread_mutex_unlock(phils->left);
	pthread_mutex_unlock(phils->right);
}

void	destroy_and_free(t_phil *phils, t_data *data, int i)
{
	destroy_mutexes(i, data->forks);
	pthread_mutex_destroy(data->print);
	free(data->print);
	free(phils);
	data->print = NULL;
	phils = NULL;
}

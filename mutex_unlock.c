#include "philo.h"

void unlock(t_phil *phils)
{
	pthread_mutex_unlock(phils->left);
	pthread_mutex_unlock(phils->right);
}

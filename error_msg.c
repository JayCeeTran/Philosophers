#include "philo.h"

void	too_few_arguments(void)
{
	write(2, "Error\nInvalid amount of arguments.\n", 35);
}

void	invalid_argument(void)
{
	write(2, "Error\nInvalid arguments.\n", 25);
}

void	failed_malloc(void)
{
	write(2, "Error\nFailed malloc.\n", 21);
}

void	mutex_init_failed(t_phil *phils)
{
	write(2, "Error\nFailed to initialize mutexes\n", 35);
	free(phils);
}

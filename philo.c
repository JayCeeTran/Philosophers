#include "philo.h"

int	main(int ac, char **av)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if(!data)
	{
		failed_malloc();
		return(1);
	}
	if(ac < 5 || ac > 6)
	{
		too_few_arguments();
		return(1);
	}
	if(!save_arguments_in_struct(data, av))
		return(1);
	if(!initialize_phils(data))
		return(1);
	free(data);
	return(0);
}

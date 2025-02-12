#include "philo.h"

int	main(int ac, char **av)
{
	t_data data;

	if(ac < 6)
	{
		too_few_arguments();
		return(1);
	}
	if(!save_arguments_in_struct(&data, av))
		return(1);
	if(!initialize_phils(&data))
		return(1);

	return(0);
}

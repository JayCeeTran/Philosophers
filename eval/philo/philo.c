/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:36:01 by jtran             #+#    #+#             */
/*   Updated: 2025/08/25 13:36:05 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		failed_malloc();
		return (1);
	}
	if (ac < 5 || ac > 6)
	{
		too_few_arguments();
		return (1);
	}
	if (!save_arguments_in_struct(data, av))
		return (1);
	initialize_phils(data);
	free(data);
	return (0);
}

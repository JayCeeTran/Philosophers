/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:29:36 by jtran             #+#    #+#             */
/*   Updated: 2025/08/25 13:34:36 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	atoi_arguments(t_data *data, char **av)
{
	data->philos = ft_atoi(av[1]);
	data->ms_die = ft_atoi(av[2]);
	data->ms_eat = ft_atoi(av[3]);
	data->ms_sleep = ft_atoi(av[4]);
	if (av[5])
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
}

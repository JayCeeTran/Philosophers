/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:35:00 by jtran             #+#    #+#             */
/*   Updated: 2025/08/25 13:35:03 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(long start_time)
{
	struct timeval	tv;
	long			result;

	gettimeofday(&tv, NULL);
	result = tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time;
	return (result);
}

long	get_start_time(void)
{
	struct timeval	tv;
	long			result;

	gettimeofday(&tv, NULL);
	result = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (result);
}

void	*phil_1_die(t_phil *phil)
{
	pthread_mutex_lock(phil->left);
	print_mutex(phil, get_time(phil->data->start_time), "has taken a fork");
	while (!phil->data->dead)
		usleep(500);
	pthread_mutex_unlock(phil->left);
	return (NULL);
}

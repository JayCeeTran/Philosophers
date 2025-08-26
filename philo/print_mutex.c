/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:02:11 by jtran             #+#    #+#             */
/*   Updated: 2025/08/25 13:36:33 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_mutex(t_phil *phils, long time, char *s)
{
	pthread_mutex_lock(phils->print);
	if (phils->data->dead == 0)
	{
		printf("%ld %d %s\n", time, phils->id, s);
	}
	pthread_mutex_unlock(phils->print);
}

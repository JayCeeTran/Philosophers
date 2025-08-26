/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_unlock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:35:38 by jtran             #+#    #+#             */
/*   Updated: 2025/08/25 13:35:42 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock(t_phil *phils)
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

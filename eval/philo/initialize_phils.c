/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_phils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:35:07 by jtran             #+#    #+#             */
/*   Updated: 2025/08/25 13:39:52 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	fill_phils(t_phil *phils, t_data *data, int i, int j);
static void	initialize_phil_struct(t_phil *phil, t_data *data, int i);

int	initialize_phils(t_data *data)
{
	t_phil	*phils;

	phils = malloc(data->philos * sizeof(t_phil));
	if (!phils)
	{
		failed_malloc();
		return (0);
	}
	if (!fill_phils(phils, data, 0, 0))
	{
		free(phils);
		return (0);
	}
	if (!create_thread(phils, 0))
		return (0);
	destroy_and_free(phils, phils->data, phils->data->philos);
	return (1);
}

static int	fill_phils(t_phil *phils, t_data *data, int i, int j)
{
	data->print = malloc(sizeof(pthread_mutex_t));
	if (!data->print)
		return (0);
	if (pthread_mutex_init(data->print, NULL))
	{
		free(data->print);
		return (0);
	}
	data->forks = malloc(data->philos * sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		destroy_and_free(phils, phils->data, -1);
		return (0);
	}
	while (j < data->philos)
	{
		if (pthread_mutex_init(&data->forks[j++], NULL))
		{
			mutex_init_failed(phils);
			destroy_and_free(phils, phils->data, --j);
			return (0);
		}
	}
	initialize_phil_struct(phils, data, i);
	return (1);
}

void	initialize_phil_struct(t_phil *phils, t_data *data, int i)
{
	while (i < data->philos)
	{
		phils[i].id = i + 1;
		phils[i].last_meal_time = 0;
		phils[i].meals = 0;
		phils[i].print = data->print;
		phils[i].data = data;
		phils[i].left = &data->forks[i];
		if (data->philos == 1)
		{
			phils[i].right = NULL;
			break ;
		}
		phils[i].right = &data->forks[(i + 1) % data->philos];
		i++;
	}
}

void	destroy_mutexes(int i, pthread_mutex_t *forks)
{
	while (--i >= 0)
	{
		pthread_mutex_destroy(&forks[i]);
	}
	free(forks);
	forks = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:02:11 by jtran             #+#    #+#             */
/*   Updated: 2025/08/24 13:22:29 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_mutex(t_phil *phils, long time, char *s)
{
	pthread_mutex_lock(phils->print);
	if(phils->data->dead == 0)
	{
		printf("%ld %d %s\n", time, phils->id, s);
	}
	pthread_mutex_unlock(phils->print);
}

int   dead(t_phil *phils, long start_time)
{
    long time = get_time(start_time);
    if(phils->data->dead == 1)
	    return(0);
    if(phils->round != 0)
    {
        if(time - phils->last_meal_time > phils->data->ms_die)
        {
	    print_mutex(phils, time, "died");
            phils->data->dead = 1;
	    return(1);
        }
    }
    else if(time > phils->data->ms_die)
    {
	   print_mutex(phils, time, "died");
	   phils->data->dead = 1;
	   return(1);
    }
    return(0);
}

int   check_dead(t_phil *phils)
{
    if(phils->data->dead == 1)
    {
        return(1);
    }
    return(0);
}

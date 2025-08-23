/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:02:11 by jtran             #+#    #+#             */
/*   Updated: 2025/03/04 11:00:19 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int   dead(t_phil *phils, long start_time)
{
    long time = get_time(start_time);
    if(phils->data->dead == 1)
	    return(0);
    if(phils->round != 0)
    {
        if(time - phils->last_meal_time > phils->data->ms_die)
        {
	    pthread_mutex_lock(phils->print);
            printf("%ld %d died\n", time, phils->id);
	    pthread_mutex_unlock(phils->print);
            phils->data->dead = 1;
	    return(1);
        }
    }
    else if(time > phils->data->ms_die)
    {
	   pthread_mutex_lock(phils->print);
           printf("%ld %d died\\n", time, phils->id);
	   pthread_mutex_unlock(phils->print);
           phils->data->dead = 1;
	   return(1);
    }
    return(0);
}

int   check_dead(t_phil *phils)
{
    if(phils->data->dead == 1)
    {
//	pthread_mutex_lock(phils->print);        
  //      printf("Phil %d noticed someone died. Time of notice: %ld\n", phils->id, get_time(phils->data->start_time));
//	pthread_mutex_unlock(phils->print);
        return(0);
    }
    return(1);
}

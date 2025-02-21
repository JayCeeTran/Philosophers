/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtran <jtran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:02:11 by jtran             #+#    #+#             */
/*   Updated: 2025/02/21 14:39:07 by jtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    dead(t_phil *phils, long otime)
{
    long time = get_time();
    if(phils->last_meal_time != 0)
    {
        if(time - phils->last_meal_time > phils->data->ms_die)
            phils->data->dead = 1;
    }
    else if(time - otime > phils->data->ms_die)
    {
        phils->data->dead = 1;
    }
    if(phils->data->dead == 1)
    {
        pthread_cancel(phils->thread);
        pthread_join(phils->thread, NULL);
        printf("phil %d died\n", phils->id);
    }
}

void    check_dead(t_phil *phils)
{
    if(phils->data->dead == 1)
    {
        pthread_cancel(phils->thread);
        pthread_join(phils->thread, NULL);
        printf("someone died\n");
    }
}
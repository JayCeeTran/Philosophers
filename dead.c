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

void    dead(t_phil *phils, long otime)
{
    long time = get_time();
    if(phils->last_meal_time != 0)
    {
        if(time - phils->last_meal_time > phils->data->ms_die)
        {
            printf("dead guy %d\n", phils->id);
            phils->data->dead = 1;
        }
    }
    otime++;
    /*else if(time - otime > phils->data->ms_die)
    {
            printf("dead guy %d\n", phils->id);
            phils->data->dead = 1;
    }*/

}

void    *check_dead(t_phil *phils)
{
    if(phils->data->dead == 1)
    {
        
        printf("%d someone died\n", phils->id);
        return(NULL);
    }
    return((void*)phils);
}
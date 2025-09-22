/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:31:44 by midiagne          #+#    #+#             */
/*   Updated: 2025/09/21 20:49:03 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    precise_sleep(int ms)
{
    // gettimeof day
    if (ms <= 10)
    {
        // busy-work
    }
    else if (ms > 10)
    {
        // usleep pdt 75% du temps, puis je get le realtimeslept en faisant gettimeofday apres usleep - gettimeoffay initial
        // et je busy-work pour le temps restant
    }
}
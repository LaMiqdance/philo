/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 00:50:14 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/04 01:19:01 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    init_philo(t_philo **philo, t_data *data, int index)
{
    t_philo *str;

    str = malloc(sizeof(t_philo));
    if (!str)
    {
        
    }
    str = philo[index];
    
}
    
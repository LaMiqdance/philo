/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:06:26 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/13 00:25:15 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int    check_death(t_philo **philo, int nb_philo)
{
    int i;

    i = 0;
    while (i < nb_philo)
    {
        pthread_mutex_lock(&philo[i]->m_last_meal_time);
        if (get_current_time_ms() - philo[i]->last_meal_time > philo[i]->glb_data->time_to_die)
        {
            pthread_mutex_unlock(&philo[i]->m_last_meal_time);
            pthread_mutex_lock(&philo[i]->glb_data->m_simu_stop);
            philo[i]->glb_data->simu_stop = 1;
            pthread_mutex_unlock(&philo[i]->glb_data->m_simu_stop);
            mutex_print(*philo);
            return (1);
        }
        pthread_mutex_unlock(&philo[i]->m_last_meal_time);
        i++;
    }
    return (0);
}

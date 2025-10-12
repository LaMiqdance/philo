/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:06:26 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/13 00:44:09 by midiagne         ###   ########.fr       */
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
            philo[i]->has_died = 1;
            mutex_print(philo[i]);
            return (1);
        }
        pthread_mutex_unlock(&philo[i]->m_last_meal_time);
        i++;
    }
    return (0);
}

void    *monitor_routine(void *arg)
{
    t_philo **philos;

    philos = (t_philo**)arg;
    while (1)
    {
        pthread_mutex_lock(&(*philos)->glb_data->m_simu_stop);
        if (check_death(philos, (*philos)->glb_data->nb_philo) == 1)
        {
            pthread_mutex_unlock(&(*philos)->glb_data->m_simu_stop);
            // nettoyer
            return (NULL);
        }
        pthread_mutex_unlock(&(*philos)->glb_data->m_simu_stop);
        precise_timing((*philos)->glb_data->time_to_die / 5);
    }
}

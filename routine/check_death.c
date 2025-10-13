/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:06:26 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/13 02:43:02 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int    check_death(t_philo **philo, int nb_philo)
{
    int i;
    unsigned long long time_since_meal;

    i = 0;
    while (i < nb_philo)
    {
        pthread_mutex_lock(&philo[i]->m_last_meal_time);
        time_since_meal = get_current_time_ms() - philo[i]->last_meal_time;
        if (time_since_meal > philo[i]->glb_data->time_to_die)
        {
            pthread_mutex_unlock(&philo[i]->m_last_meal_time);
            philo[i]->glb_data->simu_stop = 1;
            philo[i]->has_died = 1;
            printf(">>> ABOUT TO PRINT DEATH MESSAGE FOR PHILO %d <<<\n", philo[i]->id);
            mutex_print(philo[i]);
            printf(">>> DEATH MESSAGE PRINTED <<<\n");
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 23:14:00 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/22 23:58:07 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


int check_death(t_philo **philo, int nb_philo)
{
    int i;
    unsigned long long time;
    int is_eating;

    i = 0;
    while (i < nb_philo)
    {
        pthread_mutex_lock(&philo[i]->m_last_meal_time);
        time = get_current_time_ms() - philo[i]->last_meal_time;
        pthread_mutex_unlock(&philo[i]->m_last_meal_time);
        pthread_mutex_lock(&philo[i]->m_state);
        is_eating = philo[i]->is_eating;
        pthread_mutex_unlock(&philo[i]->m_state);
        if (time > philo[i]->glb_data->time_to_die)
        {
            pthread_mutex_lock(&philo[i]->glb_data->m_simu_stop);
			philo[i]->glb_data->simu_stop = 1;
			pthread_mutex_unlock(&philo[i]->glb_data->m_simu_stop);
			pthread_mutex_lock(&philo[i]->m_state);
			philo[i]->has_died = 1;
			pthread_mutex_unlock(&philo[i]->m_state);
            print_status(philo[i], "has died", time);
            return (1);
        }
        i++;
    }
    return (0);
}

void    *monitor_routine(void *arg)
{
    (void)arg;
    return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 23:14:00 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/23 23:56:42 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int check_meals_eaten(t_philo **philo, int nb_philo)
{
    int	i;

	i = 0;
	if ((*philo)->glb_data->number_of_times_each_philosopher_must_eat == 0)
		return (0);
    printf("DEBUG: Checking meals, target = %d\n", (*philo)->glb_data->number_of_times_each_philosopher_must_eat);
	while (i < nb_philo)
	{
		pthread_mutex_lock(&philo[i]->m_meals_eaten);
        printf("DEBUG: Philo %d has eaten %d times\n", philo[i]->id, philo[i]->meals_eaten);
		if (philo[i]->meals_eaten
			>= philo[i]->glb_data->number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_unlock(&philo[i]->m_meals_eaten);
			i++;
		}
		else
		{
			pthread_mutex_unlock(&philo[i]->m_meals_eaten);
			return (0);
		}
	}
    printf("DEBUG: All philosophers have eaten enough! Stopping simulation.\n");
	pthread_mutex_lock(&(*philo)->glb_data->m_simu_stop);
	(*philo)->glb_data->simu_stop = 1;
	pthread_mutex_unlock(&(*philo)->glb_data->m_simu_stop);
	return (1);
}

int check_death(t_philo **philo, int nb_philo)
{
    int i;
    unsigned long long time;

    i = 0;
    while (i < nb_philo)
    {
        pthread_mutex_lock(&philo[i]->m_last_meal_time);
        time = get_current_time_ms() - philo[i]->last_meal_time;
        pthread_mutex_unlock(&philo[i]->m_last_meal_time);

        if (time > philo[i]->glb_data->time_to_die)
        {
            pthread_mutex_lock(&philo[i]->glb_data->m_print); // pour pas que des choses soient ecrites apres la mort
            pthread_mutex_lock(&philo[i]->glb_data->m_simu_stop);
			philo[i]->glb_data->simu_stop = 1;
			pthread_mutex_unlock(&philo[i]->glb_data->m_simu_stop);

            time = get_current_time_ms();
            printf("%llu %d died\n", time - philo[i]->glb_data->start_time, philo[i]->id);
            pthread_mutex_unlock(&philo[i]->glb_data->m_print);
            return (1);
        }
        i++;
    }
    return (0);
}

void    *monitor_routine(void *arg)
{
    t_philo **philo;

    philo = (t_philo **)arg;
    while (1)
    {
        if (check_death(philo, (*philo)->glb_data->nb_philo)
        || check_meals_eaten(philo, (*philo)->glb_data->nb_philo))
            return (NULL);
        precise_timing(7);
    }
}

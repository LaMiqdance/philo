/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:33:13 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/14 11:21:39 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*only_philo(t_philo *philo)
{
	if (philo->glb_data->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->glb_data->forks[0]);
		philo->has_taken_a_fork = 1;
		mutex_print(philo);
		pthread_mutex_unlock(&philo->glb_data->forks[0]);
		return (NULL);
	}
	return (philo);
}

void	mutex_print(t_philo *philo)
{
	pthread_mutex_lock(&philo->glb_data->m_print);
	time_print(philo);
	pthread_mutex_unlock(&philo->glb_data->m_print);
}

void	my_guy_is_eating(t_philo *philo)
{
	philo->is_eating = 1;
	mutex_print(philo);
	lock_last_meal_time(philo);
	precise_timing(philo->glb_data->time_to_eat);
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
}


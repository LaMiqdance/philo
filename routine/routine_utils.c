/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:23:55 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/16 11:37:12 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	lock_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_last_meal_time);
	philo->last_meal_time = get_current_time_ms();
	pthread_mutex_unlock(&philo->m_last_meal_time);
}

void	mutex_print(t_philo *philo)
{
	pthread_mutex_lock(&philo->glb_data->m_print);
	time_print(philo);
	pthread_mutex_unlock(&philo->glb_data->m_print);
}

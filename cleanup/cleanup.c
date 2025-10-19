/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:35:56 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/19 17:42:58 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	cleanup_mutex(pthread_mutex_t *mutex, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
	free(mutex);
}

void	cleanup_philos(t_philo **philo, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (philo[i])
		{
			pthread_mutex_destroy(&philo[i]->m_has_taken_a_fork);
			pthread_mutex_destroy(&philo[i]->m_is_eating);
			pthread_mutex_destroy(&philo[i]->m_is_thinking);
			pthread_mutex_destroy(&philo[i]->m_is_sleeping);
			pthread_mutex_destroy(&philo[i]->last_meal_time);
			pthread_mutex_destroy(&philo[i]->m_meals_eaten);
			pthread_mutex_destroy(&philo[i]->m_has_died);
		}
		i++;
	}
	free(philo);
}

// cleanup_n_exit(data)
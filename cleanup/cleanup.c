/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 03:17:10 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/05 01:29:41 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	cleanup_philos(t_philo **philo, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		pthread_mutex_destroy(&philo[i]->m_last_meal_time);
		free(philo[i]);
		i++;
	}
	free(philo);
}

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

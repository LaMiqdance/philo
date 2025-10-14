/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:10:36 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/14 19:39:20 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	final_cleanup(t_philo **philo, t_data *data, pthread_t *thread_ids)
{
	cleanup_philos(philo, data->nb_philo, 0);
	cleanup_philos(philo, data->nb_philo, 1);
	free(data->forks);
	free(thread_ids);
	pthread_mutex_destroy(&data->m_simu_stop);
	pthread_mutex_destroy(&data->m_print);
	free(data);
}

void	cleanup_philos(t_philo **philo, int index, int mutex)
{
	int	i;

	i = 0;
	if (mutex == -1)
		free(philo);
	while (i < index)
	{
		if (mutex == 0)
			pthread_mutex_destroy(&philo[i]->m_last_meal_time);
		else if (mutex == 1)
			pthread_mutex_destroy(&philo[i]->m_state);
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

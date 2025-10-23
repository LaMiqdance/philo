/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:35:56 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/23 23:38:55 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	cleanup_data(t_data *data)
{
	pthread_mutex_destroy(&data->m_simu_stop);
	pthread_mutex_destroy(&data->m_print);
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

void	cleanup_philos(t_philo **philo, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (philo[i])
		{
			pthread_mutex_destroy(&philo[i]->m_meals_eaten);
			pthread_mutex_destroy(&philo[i]->m_last_meal_time);
			free(philo[i]);
		}
		i++;
	}
	free(philo);
}

void	final_cleanup(t_philo **philo, t_data *data, pthread_t *thread_ids)
{
	cleanup_philos(philo, data->nb_philo);
	free(thread_ids);
	cleanup_mutex(data->forks, data->nb_philo);
	free(data->forks);
	cleanup_data(data);
	free(data);
}
// cleanup_n_exit(data)
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>           +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 00:50:14 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/09 17:44:44 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_threads(pthread_t *threads_ids, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < ((philo[0])->glb_data->nb_philo))
	{
		if ((pthread_create(&threads_ids[i], NULL, philosopher_routine,
					philo[i])) != 0)
		{
			pthread_mutex_lock(&philo[i]->glb_data->m_simu_stop);
			philo[i]->glb_data->simu_stop = 1;
			pthread_mutex_unlock(&philo[i]->glb_data->m_simu_stop);
			while (i > 0)
			{
				pthread_join(threads_ids[i - 1], NULL);
				i--;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

pthread_mutex_t	*init_forks(t_data *data)
{
	int	i;
	int	r;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (NULL);
	while (i < data->nb_philo)
	{
		r = pthread_mutex_init(&data->forks[i], NULL);
		if (r != 0)
		{
			cleanup_mutex(data->forks, i);
			return (NULL);
		}
		i++;
	}
	return (data->forks);
}

t_philo	**init_philo(t_data *data)
{
	int		i;
	int		r;
	int		s;
	t_philo	**philo;

	philo = malloc(sizeof(t_philo *) * data->nb_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		philo[i] = fill_philo_subpart(data, i);
		if (!philo[i])
			return (cleanup_philos(philo, i, -1), NULL);
		init_states(philo[i]);
		r = pthread_mutex_init(&philo[i]->m_last_meal_time, NULL);
		if (r != 0)
		{
			free(philo[i]);
			return (cleanup_philos(philo, i, -1), NULL);
		}
		s = pthread_mutex_init(&philo[i]->m_state, NULL);
		if (s != 0)
		{
			pthread_mutex_destroy(&philo[i]->m_last_meal_time);
			free(philo[i]);
			return (cleanup_philos(philo, i, -1), NULL);
		}
		i++;
	}
	return (philo);
}

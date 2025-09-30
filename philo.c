/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:12:06 by midiagne          #+#    #+#             */
/*   Updated: 2025/09/30 15:18:20 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	main(int ac, char **av)
{
	t_data		*data;
	pthread_t	*thread_ids;
	t_philo		**philo;
	int			i;

	data = fill_struct(ac, av);
	if (!data)
		return (1);
	thread_ids = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!thread_ids)
		return (free(data), 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (free(data), free(thread_ids), 1);
	i = 0;
	pthread_mutex_init(&data->m_simu_stop, NULL);
	data->simu_stop = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
 	philo = malloc(sizeof(t_philo *) * data->nb_philo);
	i = 0;
	if (!philo)
		return (free(data), free(thread_ids), free(data->forks), 1);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&philo[i]->last_meal_time, NULL);
		i++;
	}
	// creation des threads
	//  execution de la routine par chaque thread
}

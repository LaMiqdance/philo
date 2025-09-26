/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:12:06 by midiagne          #+#    #+#             */
/*   Updated: 2025/09/26 20:05:17 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo				*philo;

	philo = (t_philo *)arg;
	philo->last_meal_time = get_current_time_in_ms();
	if (philo->id % 2 == 0)
	{
	}
	else
	{
	}
}

int	main(int ac, char **av)
{
	t_data		*data;
	pthread_t	*thread_ids;
	int			i;

	data = fill_struct(ac, av);
	if (!data)
		return (-1);
    thread_ids = malloc(sizeof(pthread_t) * data->nb_philo);
    if (!thread_ids)
        return (free(data), -1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (free(data), free(thread_ids), -1);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	// creation des threads
	// execution de la routine par chaque thread
}

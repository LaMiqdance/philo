/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:48:13 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/14 12:02:21 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*fill_philo_subpart(t_data *data, int i)
{
	t_philo	*philo;
	t_philo	*str;

	str = malloc(sizeof(t_philo));
	if (!str)
		return (NULL);
	philo = str;
	philo->id = i + 1;
	philo->glb_data = data;
	philo->last_meal_time = get_current_time_ms();
	return (philo);
}

int	init_data(t_data *data)
{
	pthread_mutex_init(&data->m_simu_stop, NULL);
	pthread_mutex_init(&data->m_print, NULL);
	data->simu_stop = 0;
	data->start_time = get_current_time_ms();
	return (1);
}

void	init_states(t_philo *philo)
{
	philo->is_thinking = 0;
	philo->has_taken_a_fork = 0;
	philo->is_eating = 0;
	philo->is_sleeping = 0;
	philo->has_died = 0;
	philo->meals_eaten = 0;
}

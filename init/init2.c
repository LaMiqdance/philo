/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:20:10 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/23 23:53:59 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*fill_philo_subpart(t_data *data, int i)
{
	t_philo	*philo;
	
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = i + 1;
	philo->glb_data = data;
	philo->last_meal_time = get_current_time_ms();
	philo->left_fork = &data->forks[i];
    philo->right_fork = &data->forks[(i + 1) % data->nb_philo];
    
	return (philo);
}

int	init_data(t_data *data)
{
	if (pthread_mutex_init(&data->m_simu_stop, NULL))
		return (0);
	if (pthread_mutex_init(&data->m_print, NULL))
	{
		pthread_mutex_destroy(&data->m_simu_stop);
		return (0);
	}
	data->simu_stop = 0;
	data->start_time = get_current_time_ms();
	return (1);
}

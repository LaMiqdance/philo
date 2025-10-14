/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:20:16 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/14 20:39:19 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	lock_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_last_meal_time);
	philo->last_meal_time = get_current_time_ms();
	pthread_mutex_unlock(&philo->m_last_meal_time);
}

int		take_fork(t_philo *philo, int fork_index)
{
	pthread_mutex_lock(&philo->glb_data->forks[fork_index]);
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	if (philo->glb_data->simu_stop == 1 || philo->has_died == 1)
	{
		pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
		pthread_mutex_unlock(&philo->glb_data->forks[fork_index]);
		return (0);
	}
	pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
	pthread_mutex_lock(&philo->m_state);
	philo->has_taken_a_fork = 1;
	pthread_mutex_unlock(&philo->m_state);
	mutex_print(philo);
	return (1);
}


void	unlock_which_first(t_philo *philo)
{
	
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->glb_data->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->glb_data->forks[philo->id
			% (philo->glb_data->nb_philo)]);
	}
	else
	{
		pthread_mutex_unlock(&philo->glb_data->forks[philo->id
			% (philo->glb_data->nb_philo)]);
		pthread_mutex_unlock(&philo->glb_data->forks[philo->id - 1]);
	}
}

void	set_sleeping_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_state);
	philo->is_eating = 0;
	philo->has_taken_a_fork = 0;
	philo->is_sleeping = 1;
	pthread_mutex_unlock(&philo->m_state);
}

void	set_thinking_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_state);
	philo->is_sleeping = 0;
	philo->is_thinking = 1;
	pthread_mutex_unlock(&philo->m_state);
}

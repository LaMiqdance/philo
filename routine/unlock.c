/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlock.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:16:09 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/15 13:40:29 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	unlock_which_first(t_philo *philo)
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

static int	state_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	pthread_mutex_lock(&philo->m_state);
	if (!philo->has_died && philo->glb_data->simu_stop == 0)
		mutex_print(philo);
	if (philo->glb_data->simu_stop == 1 || philo->has_died == 1)
	{
		pthread_mutex_unlock(&philo->m_state);
		pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
		return (0);
	}
	pthread_mutex_unlock(&philo->m_state);
	pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
	return (1);
}

static void	set_sleeping_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_state);
	philo->is_eating = 0;
	philo->has_taken_a_fork = 0;
	philo->is_sleeping = 1;
	pthread_mutex_unlock(&philo->m_state);
}

static void	set_thinking_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_state);
	philo->is_sleeping = 0;
	philo->is_thinking = 1;
	pthread_mutex_unlock(&philo->m_state);
}

void	unlock_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	pthread_mutex_lock(&philo->m_state);
	if (philo->glb_data->simu_stop == 1 || philo->has_died == 1)
	{
		pthread_mutex_lock(&philo->m_state);
		pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
		unlock_which_first(philo);
		return ;
	}
	pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
	unlock_which_first(philo);
	set_sleeping_state(philo);
	if (!state_check(philo))
		return ;
	precise_timing(philo->glb_data->time_to_sleep);
	set_thinking_state(philo);
	if (!state_check(philo))
		return ;
	if (philo->glb_data->time_to_think > 0)
		precise_timing(philo->glb_data->time_to_think);
}

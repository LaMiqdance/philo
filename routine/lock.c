/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 07:59:39 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/18 15:39:29 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	take_fork(t_philo *philo, int fork_index)
{
	int	simu_stop;
	int	has_died;

	pthread_mutex_lock(&philo->glb_data->forks[fork_index]);
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	simu_stop = philo->glb_data->simu_stop;
	pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
	pthread_mutex_lock(&philo->m_state);
	has_died = philo->has_died;
	philo->has_taken_a_fork = 1;
	pthread_mutex_unlock(&philo->m_state);
	if (simu_stop == 1 || has_died == 1)
	{
		pthread_mutex_lock(&philo->m_state);
		philo->has_taken_a_fork = 0;
		pthread_mutex_unlock(&philo->m_state);
		pthread_mutex_unlock(&philo->glb_data->forks[fork_index]);
		return (0);
	}
	mutex_print(philo);
	return (1);
}

static int	check_forks_succesfully_taken(t_philo *philo)
{
	int	first_fork;
	int	second_fork;
	int	idx_first;
	int	idx_second;

	if (philo->id % 2 == 0)
	{
		idx_first = philo->id - 1;
		idx_second = philo->id % philo->glb_data->nb_philo;
	}
	else
	{
		idx_first = philo->id % philo->glb_data->nb_philo;
		idx_second = philo->id - 1;
	}
	first_fork = take_fork(philo, idx_first);
	if (!first_fork)
		return (0);
	second_fork = take_fork(philo, idx_second);
	if (!second_fork)
	{
		pthread_mutex_unlock(&philo->glb_data->forks[idx_first]);
		return (0);
	}
	return (1);
}

static void	my_guy_is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_state);
	philo->is_eating = 1;
	philo->has_taken_a_fork = 0;
	pthread_mutex_unlock(&philo->m_state);
	mutex_print(philo);
	lock_last_meal_time(philo);
	precise_timing(philo->glb_data->time_to_eat);
	pthread_mutex_lock(&philo->m_state);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->m_state);
}

int lock_fork(t_philo *philo)
{
	int simu_stop;
	int has_died;
	
	if (!check_forks_succesfully_taken(philo))
		return (0);
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	pthread_mutex_lock(&philo->m_state);
	simu_stop = philo->glb_data->simu_stop;
	has_died = philo->has_died;
	philo->is_thinking = 0;
	pthread_mutex_unlock(&philo->m_state);
	pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
	if (simu_stop == 1 || has_died == 1)
	{
		unlock_which_first(philo);
		return (0);
	}
	my_guy_is_eating(philo);
	return (1);
}

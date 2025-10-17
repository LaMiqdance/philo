/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 07:59:39 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/17 18:48:39 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	take_fork(t_philo *philo, int fork_index)
{
	pthread_mutex_lock(&philo->glb_data->forks[fork_index]);
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	if (philo->glb_data->simu_stop == 1 || philo->has_died == 1)
	{
		pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
		pthread_mutex_unlock(&philo->glb_data->forks[fork_index]);
		return (0);
	}
	pthread_mutex_lock(&philo->m_state);
	philo->has_taken_a_fork = 1;
	pthread_mutex_unlock(&philo->m_state);
	if (philo->glb_data->simu_stop == 1)
	{
		pthread_mutex_unlock(&philo->glb_data->forks[fork_index]);
		return (0);
	}
	pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
	mutex_print(philo);
	return (1);
}

static int	fork_taken_error(t_philo *philo, int first, int second)
{
	if (!first)
		return (0);
	if (!second)
	{
		if (philo->id % 2 == 0)
			pthread_mutex_unlock(&philo->glb_data->forks[philo->id - 1]);
		else
		{
			pthread_mutex_unlock(&philo->glb_data->forks[philo->id
				% philo->glb_data->nb_philo]);
		}
		return (0);
	}
	return (1);
}

static int	check_forks_succesfully_taken(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = take_fork(philo, philo->id - 1);
		second_fork = take_fork(philo, philo->id % philo->glb_data->nb_philo);
		if (!fork_taken_error(philo, first_fork, second_fork))
			return (0);
	}
	else
	{
		first_fork = take_fork(philo, philo->id % philo->glb_data->nb_philo);
		second_fork = take_fork(philo, philo->id - 1);
		if (!fork_taken_error(philo, first_fork, second_fork))
			return (0);
	}
	return (1);
}

static void	my_guy_is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_state);
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->m_state);
	mutex_print(philo);
	lock_last_meal_time(philo);
	precise_timing(philo->glb_data->time_to_eat);
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
}

int	lock_fork(t_philo *philo)
{
	if (!check_forks_succesfully_taken(philo))
		return (0);
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	if (philo->glb_data->simu_stop == 1 || philo->has_died == 1)
	{
		pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
		unlock_which_first(philo);
		return (0);
	}
	pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
	pthread_mutex_lock(&philo->m_state);
	philo->is_thinking = 0;
	pthread_mutex_unlock(&philo->m_state);
	my_guy_is_eating(philo);
	return (1);
}

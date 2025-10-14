/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlock_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:07:32 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/14 20:08:53 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	state_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	if (!philo->has_died && philo->glb_data->simu_stop == 0)
		mutex_print(philo);
	if (philo->glb_data->simu_stop == 1 || philo->has_died == 1)
	{
		pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
		return (0);
	}
	pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
	return (1);
}

int	fork_taken_error(t_philo *philo, int first, int second)
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

int	check_forks_succesfully_taken(t_philo *philo)
{
	int first_fork;
	int second_fork;

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

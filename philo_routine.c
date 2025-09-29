/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:03:19 by midiagne          #+#    #+#             */
/*   Updated: 2025/09/29 14:12:13 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->glb_info->forks[philo->id]);
		pthread_mutex_lock(&philo->glb_info->forks[philo->id + 1
			% (philo->glb_info->nb_philo)]);
	}
	else
	{
		pthread_mutex_lock(&philo->glb_info->forks[philo->id + 1
			% (philo->glb_info->nb_philo)]);
		pthread_mutex_lock(&philo->glb_info->forks[philo->id]);
	}
}
static void	unlock_fork(t_philo *philo)
{
	philo->last_meal_time = get_current_time_ms();
	precise_timing(philo->glb_info->time_to_eat);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->glb_info->forks[philo->id]);
		pthread_mutex_unlock(&philo->glb_info->forks[philo->id + 1
			% (philo->glb_info->nb_philo)]);
	}
	else
	{
		pthread_mutex_unlock(&philo->glb_info->forks[philo->id + 1
			% (philo->glb_info->nb_philo)]);
		pthread_mutex_unlock(&philo->glb_info->forks[philo->id]);
	}
	precise_timing(philo->glb_info->time_to_sleep);
}
int	fcts_summed_up(t_philo *philo)
{
	pthread_mutex_lock(&philo->glb_info->m_simu_stop);
	if (philo->glb_info->simu_stop == 1)
	{
		pthread_mutex_unlock(&philo->glb_info->m_simu_stop);
		return (free(philo), 0);
	}
	pthread_mutex_unlock(&philo->glb_info->m_simu_stop);
	lock_fork(philo);
	unlock_fork(philo);
	return (1);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	int		flag;

	philo = (t_philo *)arg;
	philo->last_meal_time = get_current_time_ms();
	flag = 1;
	while (1)
	{
		flag = fcts_summed_up(philo);
		if (flag == 0)
			return (free(philo), NULL);
	}
	return (free(philo), NULL);
}

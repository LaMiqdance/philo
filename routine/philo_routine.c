/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 02:17:24 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/17 20:12:50 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static t_philo	*only_philo(t_philo *philo)
{
	if (philo->glb_data->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->glb_data->forks[0]);
		pthread_mutex_lock(&philo->m_state);
		philo->has_taken_a_fork = 1;
		pthread_mutex_unlock(&philo->m_state);
		mutex_print(philo);
		pthread_mutex_unlock(&philo->glb_data->forks[0]);
		return (NULL);
	}
	return (philo);
}

static int	fcts_summed_up(t_philo *philo)
{
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	if (philo->glb_data->simu_stop == 1 || philo->has_died == 1)
	{
		pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
		return (0);
	}
	pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
	if (lock_fork(philo) == 1)
		unlock_fork(philo);
	else
		return (0);
	return (1);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	int		flag;

	philo = (t_philo *)arg;
	philo = only_philo(philo);
	if (!philo)
		return (NULL);
	if ((philo->id) % 2 == 1)
		usleep(1000);
	if (philo->glb_data->nb_philo % 2 == 0 && philo->id == philo->glb_data->nb_philo)
		usleep(2000);
	flag = 1;
	while (1)
	{
		flag = fcts_summed_up(philo);
		if (flag == 0)
			return (NULL);
	}
	return (NULL);
}

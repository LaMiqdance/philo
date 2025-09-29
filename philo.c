/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:12:06 by midiagne          #+#    #+#             */
/*   Updated: 2025/09/29 13:16:15 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fcts_summed_up(t_philo *philo)
{
	pthread_mutex_lock(&philo->glb_info->m_simu_stop);
	if (philo->glb_info->simu_stop == 1)
	{
		pthread_mutex_unlock(&philo->glb_info->m_simu_stop);
		return (free(philo), NULL);
	}
	else if (philo->glb_info->simu_stop == 0)
	{
		pthread_mutex_unlock(&philo->glb_info->m_simu_stop);
		lock_fork(philo);
		unlock_fork(philo);
	}
}

void	lock_fork(t_philo *philo)
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

void	unlock_fork(t_philo *philo)
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

void	*simu_stop(t_philo *philo)
{
	if (philo->glb_info->simu_stop == 1)
	{
		pthread_mutex_unlock(&philo->glb_info->m_simu_stop);
		return (free(philo), NULL);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal_time = get_current_time_ms();
	if (philo->id % 2 == 0)
	{
		while (1)
			fcts_summed_up(philo);
	}
	else if (philo->id % 2 != 0)
	{	
		while (1)
			fcts_summed_up(philo);
	}
	return (philo);
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
	pthread_mutex_init(&data->m_simu_stop, NULL);
	data->simu_stop = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	// creation des threads
	// execution de la routine par chaque thread
}

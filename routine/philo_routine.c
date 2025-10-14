/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>           +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:03:19 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/09 20:07:12 by midiagne         ###   ########.fr       */
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

void	lock_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		take_fork(philo, philo->id - 1);
		take_fork(philo, philo->id % philo->glb_data->nb_philo);
	}
	else
	{
		take_fork(philo, philo->id % philo->glb_data->nb_philo);
		take_fork(philo, philo->id - 1);
	}
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	if (philo->glb_data->simu_stop == 1 || philo->has_died == 1)
	{
		pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
		return ;
	}
	pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
	philo->is_thinking = 0;
	my_guy_is_eating(philo);
}

void	unlock_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	if (philo->glb_data->simu_stop == 1 || philo->has_died == 1)
	{
		pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
		unlock_which_first(philo);
		return ;
	}
	pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
	unlock_which_first(philo);
	philo->is_eating = 0;
	philo->has_taken_a_fork = 0;
	philo->is_sleeping = 1;
	if (!state_check(philo))
		return ;
	precise_timing(philo->glb_data->time_to_sleep);
	philo->is_sleeping = 0;
	philo->is_thinking = 1;
	state_check(philo);
	if (philo->glb_data->time_to_think > 0)
		precise_timing(philo->glb_data->time_to_think);
}

int	fcts_summed_up(t_philo *philo)
{
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	if (philo->glb_data->simu_stop == 1 || philo->has_died == 1)
	{
		pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
		return (0);
	}
	pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
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
	philo = only_philo(philo);
	if (!philo)
		return (NULL);
	flag = 1;
	while (1)
	{
		flag = fcts_summed_up(philo);
		if (flag == 0)
			return (NULL);
	}
	return (NULL);
}

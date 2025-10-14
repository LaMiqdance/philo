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

int	lock_fork(t_philo *philo)
{
	if (!check_forks_succesfully_taken(philo))
		return (0);
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	if (philo->glb_data->simu_stop == 1 || philo->has_died == 1)
	{
		pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
		return (0);
	}
	pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
	philo->is_thinking = 0;
	my_guy_is_eating(philo);
	return (1);
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

int	fcts_summed_up(t_philo *philo)
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
	usleep((philo->id % 2) * 1000);
	flag = 1;
	while (1)
	{
		flag = fcts_summed_up(philo);
		if (flag == 0)
			return (NULL);
	}
	return (NULL);
}

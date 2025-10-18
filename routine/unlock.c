/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlock.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:16:09 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/18 14:05:31 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	unlock_which_first(t_philo *philo)
{
    int	nb;
    int	left;
    int	right;

    nb = philo->glb_data->nb_philo;
    left = philo->id - 1;
    right = philo->id % nb;
    if (left == right)
    {
        /* cas nb_philo == 1 : une seule fourchette */
        pthread_mutex_unlock(&philo->glb_data->forks[left]);
        return ;
    }
    if (philo->id % 2 == 0)
    {
        pthread_mutex_unlock(&philo->glb_data->forks[left]);
        pthread_mutex_unlock(&philo->glb_data->forks[right]);
    }
    else
    {
        pthread_mutex_unlock(&philo->glb_data->forks[right]);
        pthread_mutex_unlock(&philo->glb_data->forks[left]);
    }
}

static int state_check(t_philo *philo)
{
    int simu_stop;
    int has_died;
    int should_print;
    
    pthread_mutex_lock(&philo->glb_data->m_simu_stop);
    pthread_mutex_lock(&philo->m_state);
    
    simu_stop = philo->glb_data->simu_stop;
    has_died = philo->has_died;
    should_print = (!has_died && simu_stop == 0);
    
    pthread_mutex_unlock(&philo->m_state);
    pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
    
    if (should_print)
        mutex_print(philo);
    
    if (simu_stop == 1 || has_died == 1)
        return (0);
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
	int simu_stop;
	int has_died;
	
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	simu_stop = philo->glb_data->simu_stop;
	pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
	pthread_mutex_lock(&philo->m_state);
	has_died = philo->has_died;
	pthread_mutex_unlock(&philo->m_state);
	if (simu_stop == 1 || has_died == 1)
	{
		unlock_which_first(philo);
		return ;
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 07:59:39 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/18 13:45:25 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int		take_fork(t_philo *philo, int fork_index)
{
    pthread_mutex_lock(&philo->glb_data->forks[fork_index]);
    pthread_mutex_lock(&philo->glb_data->m_simu_stop);
    pthread_mutex_lock(&philo->m_state);
    if (philo->glb_data->simu_stop == 1 || philo->has_died == 1)
    {
        pthread_mutex_unlock(&philo->m_state);
        pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
        pthread_mutex_unlock(&philo->glb_data->forks[fork_index]);
        return (0);
    }
    philo->has_taken_a_fork = 1;
    pthread_mutex_unlock(&philo->m_state);
    pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
    mutex_print(philo);
    return (1);
}

static int check_forks_succesfully_taken(t_philo *philo)
{
    int first_fork;
    int second_fork;
    int idx_first;
    int idx_second;
	
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
        /* libérer la première si la seconde a échoué */
        pthread_mutex_unlock(&philo->glb_data->forks[idx_first]);
        return (0);
    }
    /* les deux forks ont été pris : marquer under m_state */
    pthread_mutex_lock(&philo->m_state);
    philo->has_taken_a_fork = 1;
    pthread_mutex_unlock(&philo->m_state);
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
	pthread_mutex_lock(&philo->m_state);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->m_state);
}

int	lock_fork(t_philo *philo)
{
	if (!check_forks_succesfully_taken(philo))
		return (0);
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	pthread_mutex_lock(&philo->m_state);
	if (philo->glb_data->simu_stop == 1 || philo->has_died == 1)
	{
		pthread_mutex_unlock(&philo->m_state);
		pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
		unlock_which_first(philo);
		return (0);
	}
	pthread_mutex_unlock(&philo->m_state);
	pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
	pthread_mutex_lock(&philo->m_state);
	philo->is_thinking = 0;
	pthread_mutex_unlock(&philo->m_state);
	my_guy_is_eating(philo);
	return (1);
}

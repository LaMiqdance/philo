/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:48:07 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/20 21:42:52 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int check_simu_stop(t_philo *philo)
{
    int should_stop;
    
    pthread_mutex_lock(&philo->glb_data->m_simu_stop);
    should_stop = philo->glb_data->simu_stop;
    pthread_mutex_unlock(&philo->glb_data->m_simu_stop);
    
    return (should_stop);
}

int     take_forks(t_philo *philo)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    if (philo->left_fork < philo->right_fork)
    {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    }
    else
    {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    }
    pthread_mutex_lock(first_fork);
    pthread_mutex_lock(second_fork);
    return (1);
}

void    sleep(t_philo *philo)
{
    precise_timing(philo->glb_data->time_to_sleep);
}

int     release_forks(t_philo *philo)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    if (philo->left_fork < philo->right_fork)
    {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    }
    else
    {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    }
    pthread_mutex_unlock(first_fork);
    pthread_mutex_unlock(second_fork);
    return (1);
}

void    eat(t_philo *philo)
{
    take_forks(philo);
    pthread_mutex_lock(&philo->m_last_meal_time);
    philo->last_meal_time = get_current_time_ms();
    pthread_mutex_unlock(&philo->m_last_meal_time);
    
    pthread_mutex_lock(&philo->m_meals_eaten);
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->m_meals_eaten);
    
    precise_timing(philo->glb_data->time_to_eat);
    release_forks(philo);
}

void    *philosopher_routine(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    pthread_mutex_lock(&philo->glb_data->m_simu_stop);
    while (!check_simu_stop(philo))
    {
       
        eat(philo);
        if (check_simu_stop(philo))
            break;
        sleep(philo);
        if (check_simu_stop(philo))
            break;
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:48:07 by midiagne          #+#    #+#             */
/*   Updated: 2025/11/04 08:03:01 by midiagne         ###   ########.fr       */
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

/* static unsigned long long calculate_thinking_time(t_philo *philo)
{
    unsigned long long base_time = (philo->glb_data->time_to_eat * philo->glb_data->nb_philo) / 8;
    unsigned long long variation = (philo->id * philo->glb_data->time_to_eat) / 20;
    return (base_time + variation);
} */

static void philo_think(t_philo *philo)
{
    unsigned long long time;

    time = get_current_time_ms();
    print_status(philo, "is thinking", time);
    precise_timing(0);
}

static int     release_forks(t_philo *philo)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    if (philo->id % 2 == 0)
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
static int     take_forks(t_philo *philo)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;
    unsigned long long time;
    
    if (philo->left_fork == philo->right_fork)
    {
        pthread_mutex_lock(philo->left_fork);
        time = get_current_time_ms();
        print_status(philo, "has taken a fork", time);
        // Wait until death; monitor will detect and stop the simulation
        precise_timing((int)philo->glb_data->time_to_die);
        pthread_mutex_unlock(philo->left_fork);
        return (0);
    }
    if (philo->id % 2 == 0)
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
    time = get_current_time_ms();
    print_status(philo, "has taken a fork", time);
    if (check_simu_stop(philo))
        return (pthread_mutex_unlock(first_fork), 0);
    pthread_mutex_lock(second_fork);
    time = get_current_time_ms();
    print_status(philo, "has taken a fork", time);
    if (check_simu_stop(philo))
        return (release_forks(philo), 0);
    return (1);
}

static void    philo_sleep(t_philo *philo)
{
    unsigned long long time;

    time = get_current_time_ms();
    print_status(philo, "is sleeping", time);
    precise_timing((int)philo->glb_data->time_to_sleep);
}


static void    eat(t_philo *philo)
{
    unsigned long long time;

    if (!take_forks(philo))
        return ;
    pthread_mutex_lock(&philo->m_last_meal_time);
    philo->last_meal_time = get_current_time_ms();
    pthread_mutex_unlock(&philo->m_last_meal_time);
    
    pthread_mutex_lock(&philo->m_meals_eaten);
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->m_meals_eaten);
    
    time = get_current_time_ms();
    print_status(philo, "is eating", time);
    precise_timing((int)philo->glb_data->time_to_eat);
    release_forks(philo);
}

void    *philosopher_routine(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    
    while (1)
    {
        if (philo->id % 2 == 0)
            usleep(1000);
        eat(philo);
        if (check_simu_stop(philo))
            break;
        philo_sleep(philo);
        if (check_simu_stop(philo))
            break;
        philo_think(philo);
        if (check_simu_stop(philo))
            break;
    }
    return (NULL);
}

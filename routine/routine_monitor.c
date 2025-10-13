/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:06:26 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/13 19:49:51 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_meals_eaten(t_philo **philo, int nb_philo)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if ((*philo)->glb_data->number_of_times_each_philosopher_must_eat == 0)
		return (0);
	while (i < nb_philo)
	{
		if (philo[i]->meals_eaten == philo[i]->glb_data->number_of_times_each_philosopher_must_eat)
		{
			count++;
			i++;
		}
		else
			return (0);
	}
	(*philo)->glb_data->simu_stop = 1;
	return (1);
}

int	check_death(t_philo **philo, int nb_philo)
{
	int					i;
	unsigned long long	time_since_meal;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_lock(&philo[i]->m_last_meal_time);
		time_since_meal = get_current_time_ms() - philo[i]->last_meal_time;
		if (time_since_meal > philo[i]->glb_data->time_to_die)
		{
			pthread_mutex_unlock(&philo[i]->m_last_meal_time);
			philo[i]->glb_data->simu_stop = 1;
			philo[i]->has_died = 1;
			mutex_print(philo[i]);
			return (1);
		}
		pthread_mutex_unlock(&philo[i]->m_last_meal_time);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	**philos;

	philos = (t_philo **)arg;
	// printf("monitor starting \n");
	while (1)
	{
		pthread_mutex_lock(&(*philos)->glb_data->m_simu_stop);
		if (check_death(philos, (*philos)->glb_data->nb_philo) == 1
			|| check_meals_eaten(philos, (*philos)->glb_data->nb_philo) == 1)
		{
			pthread_mutex_unlock(&(*philos)->glb_data->m_simu_stop);
			return (NULL);
		}
		pthread_mutex_unlock(&(*philos)->glb_data->m_simu_stop);
		precise_timing((*philos)->glb_data->time_to_die / 5);
	}
}

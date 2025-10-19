/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:17:14 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/19 17:53:09 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destroy_n_first_mutexes(t_philo *philo, int n)
{
    if (n >= 1)
        pthread_mutex_destroy(&philo->m_has_taken_a_fork);
    if (n >= 2)
        pthread_mutex_destroy(&philo->m_is_eating);
    if (n >= 3)
        pthread_mutex_destroy(&philo->m_is_thinking);
    if (n >= 4)
        pthread_mutex_destroy(&philo->m_is_sleeping);
    if (n >= 5)
        pthread_mutex_destroy(&philo->m_has_died);
    if (n >= 6)
        pthread_mutex_destroy(&philo->m_last_meal_time);
    if (n >= 7)
        pthread_mutex_destroy(&philo->m_meals_eaten);
}

int	init_mutex(t_philo *philo, t_data *data)
{
		if (pthread_mutex_init(&philo->m_has_taken_a_fork, NULL))
			return (0);
		if (pthread_mutex_init(&philo->m_is_eating, NULL))
			return (destroy_n_first_mutexes(philo, 1), 0);
		if (pthread_mutex_init(&philo->m_is_thinking, NULL));
			return (destroy_n_first_mutexes(philo, 2), 0);
		if (pthread_mutex_init(&philo->m_is_sleeping, NULL))
			return (destroy_n_first_mutexes(philo, 3), 0);
		if (pthread_mutex_init(&philo->m_has_died, NULL))
			return (destroy_n_first_mutexes(philo, 4), 0);
		if (pthread_mutex_init(&philo->m_last_meal_time, NULL))
			return (destroy_n_first_mutexes(philo, 5), 0);
		if (pthread_mutex_init(&philo->m_meals_eaten, NULL))
			return (destroy_n_first_mutexes(philo, 6), 0);
		return (1);
}

t_philo	**init_philos(t_data *data)
{
	int		i;
	t_philo	**philo;

	philo = malloc(sizeof(t_philo *) * data->nb_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		philo[i] = fill_philo_subpart(data, i);
		if (!philo[i])
			return (cleanup_philos(philo, i), NULL);
		if (!init_mutex(philo[i], data))
			return (cleanup_philos(philo, i), NULL);
		i++;
	}
	return (philo);
}

int	init_threads(pthread_t *threads_ids, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < ((philo[0])->glb_data->nb_philo))
	{
		if ((pthread_create(&threads_ids[i], NULL, philosopher_routine,
					philo[i])) != 0)
		{
			pthread_mutex_lock(&philo[i]->glb_data->m_simu_stop);
			philo[i]->glb_data->simu_stop = 1;
			pthread_mutex_unlock(&philo[i]->glb_data->m_simu_stop);
			while (i > 0)
			{
				pthread_join(threads_ids[i - 1], NULL);
				i--;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

pthread_mutex_t	*init_forks(t_data *data)
{
	int	i;
	int	r;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (NULL);
	while (i < data->nb_philo)
	{
		r = pthread_mutex_init(&data->forks[i], NULL);
		if (r != 0)
		{
			cleanup_mutex(data->forks, i);
			return (NULL);
		}
		i++;
	}
	return (data->forks);
}

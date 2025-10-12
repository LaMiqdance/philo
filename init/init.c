/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>           +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 00:50:14 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/09 17:44:44 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int init_data(t_data *data)
{
    pthread_mutex_init(&data->m_simu_stop, NULL);
    pthread_mutex_init(&data->m_print, NULL);
    data->simu_stop = 0;
    data->start_time = get_current_time_ms();
    return (1);
}

void	init_states(t_philo *philo)
{
	philo->is_thinking = 0;
	philo->has_taken_a_fork = 0;
	philo->is_eating = 0;
	philo->is_sleeping = 0;
	philo->has_died = 0;
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

t_philo	**init_philo(t_data *data)
{
	int		i;
	int		r;
	t_philo	**philo;
	t_philo	*str;

	philo = malloc(sizeof(t_philo *) * data->nb_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		str = malloc(sizeof(t_philo));
		if (!str)
		{
			cleanup_philos(philo, i);
			return (NULL);
		}
		philo[i] = str;
		philo[i]->id = i + 1;
		philo[i]->glb_data = data;
		philo[i]->last_meal_time = get_current_time_ms();
		r = pthread_mutex_init(&philo[i]->m_last_meal_time, NULL);
		if (r != 0)
		{
			free(str);
			cleanup_philos(philo, i);
			return (NULL);
		}
		i++;
	}
	return (philo);
}
#include <stdio.h>

/* int	main(int ac, char **av)
{
	t_data		*data;
	pthread_t	*thread_ids;
	t_philo		**philo;
	int			i;

	// Parse et initialise les structures
	data = fill_struct(ac, av);
	if (!data)
	{
		printf("Erreur: parsing echoue\n");
		return (1);
	}
	// Alloue le tableau des thread IDs
	thread_ids = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!thread_ids)
	{
		printf("Erreur: allocation thread_ids\n");
		free(data);
		return (1);
	}
	// Initialise les fourchettes
	data->forks = init_forks(data);
	if (!data->forks)
	{
		printf("Erreur: init des fourchettes\n");
		free(thread_ids);
		free(data);
		return (1);
	}
	// Initialise simu_stop
	pthread_mutex_init(&data->m_simu_stop, NULL);
	data->simu_stop = 0;
	// Initialise les philosophes
	philo = init_philo(data);
	if (!philo)
	{
		printf("Erreur: init des philosophes\n");
		cleanup_mutex(data->forks, data->nb_philo);
		free(thread_ids);
		free(data);
		return (1);
	}
	printf("=== Test init_threads ===\n");
	printf("Lancement de %d threads...\n", data->nb_philo);
	// Teste ta fonction init_threads
	if (init_threads(thread_ids, philo) != 1)
	{
		printf("Erreur: creation des threads echouee\n");
		// Les threads créés avec succès ont déjà été nettoyés par init_threads
		cleanup_philos(philo, data->nb_philo);
		cleanup_mutex(data->forks, data->nb_philo);
		free(thread_ids);
		free(data);
		return (1);
	}
	printf("Tous les threads créés avec succès!\n");
	printf("Les philosophes mangent pendant 3 secondes...\n");
	// Laisse tourner 3 secondes pour voir si ça marche
	sleep(3);
	// Arrête la simulation
	printf("Arrêt de la simulation...\n");
	pthread_mutex_lock(&data->m_simu_stop);
	data->simu_stop = 1;
	pthread_mutex_unlock(&data->m_simu_stop);
	// Attend que tous les threads se terminent
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(thread_ids[i], NULL);
		i++;
	}
	printf("Tous les threads terminés.\n");
	// Nettoie tout
	cleanup_philos(philo, data->nb_philo);
	cleanup_mutex(data->forks, data->nb_philo);
	pthread_mutex_destroy(&data->m_simu_stop);
	free(thread_ids);
	free(data);
	printf("Test terminé avec succès!\n");
	return (0);
}
 */
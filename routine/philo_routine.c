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

#include "philo.h"

void	lock_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_last_meal_time);
	philo->last_meal_time = get_current_time_ms();
	pthread_mutex_unlock(&philo->m_last_meal_time);
}

void	lock_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->glb_data->forks[philo->id - 1]);
		philo->has_taken_a_fork = 1;
		mutex_print(philo);
		pthread_mutex_lock(&philo->glb_data->forks[philo->id
			% (philo->glb_data->nb_philo)]);
		philo->has_taken_a_fork = 1;
		mutex_print(philo);

	}
	else
	{
		pthread_mutex_lock(&philo->glb_data->forks[philo->id 
			% (philo->glb_data->nb_philo)]);
		philo->has_taken_a_fork = 1;
		mutex_print(philo);
		pthread_mutex_lock(&philo->glb_data->forks[philo->id - 1]);
		philo->has_taken_a_fork = 1;
		mutex_print(philo);
	}
	philo->is_thinking = 0;
	philo->is_eating = 1;
	mutex_print(philo);
	lock_last_meal_time(philo);
	precise_timing(philo->glb_data->time_to_eat);
}

void	unlock_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->glb_data->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->glb_data->forks[philo->id
			% (philo->glb_data->nb_philo)]);
	}
	else
	{
		pthread_mutex_unlock(&philo->glb_data->forks[philo->id
			% (philo->glb_data->nb_philo)]);
		pthread_mutex_unlock(&philo->glb_data->forks[philo->id - 1]);
	}
	philo->is_eating = 0;
	philo->is_sleeping = 1;
	mutex_print(philo);
	precise_timing(philo->glb_data->time_to_sleep);
}

int	fcts_summed_up(t_philo *philo)
{
	pthread_mutex_lock(&philo->glb_data->m_simu_stop);
	if (philo->glb_data->simu_stop == 1)
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
	flag = 1;
	while (1)
	{
		flag = fcts_summed_up(philo);
		if (flag == 0)
			return (NULL);
	}
	return (NULL);
}
/*
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int	test_mutex_operations(t_data *data)
{
	int	i;
	int	errors;

	i = 0;
	errors = 0;
	printf("Test des opérations lock/unlock sur %d fourchettes...\n",
		data->nb_philo);
	while (i < data->nb_philo)
	{
		printf("  Test fourchette %d: ", i);
		// Test lock
		if (pthread_mutex_lock(&data->forks[i]) != 0)
		{
			printf("ERREUR - Lock failed\n");
			errors++;
		}
		else
		{
			// Test unlock
			if (pthread_mutex_unlock(&data->forks[i]) != 0)
			{
				printf("ERREUR - Unlock failed\n");
				errors++;
			}
			else
			{
				printf("OK\n");
			}
		}
		i++;
	}
	if (errors == 0)
		printf("✅ Tous les mutex fonctionnent correctement!\n");
	else
		printf("❌ %d erreurs détectées\n", errors);
	return (errors);
}

void	cleanup_forks(t_data *data)
{
	int		i;
	t_data	data;
	int		i;
	int		test_sizes[] = {1, 2, 5, 10};
	int		num_tests;

	if (!data->forks)
		return ;
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
} */
/* int main(void)
{
	printf("=== TEST D'INITIALISATION DES FOURCHETTES ===\n");
	// Test avec différents nombres de philosophes
	num_tests = sizeof(test_sizes) / sizeof(test_sizes[0]);
	for (int test = 0; test < num_tests; test++)
	{
		data.nb_philo = test_sizes[test];
		printf("\n🧪 Test avec %d philosophes:\n", data.nb_philo);
		// Allocation
		data.forks = malloc(sizeof(pthread_mutex_t) * data.nb_philo);
		if (!data.forks)
		{
			printf("❌ Erreur d'allocation\n");
			continue ;
		}
		// Initialisation
		printf("Initialisation des mutex...\n");
		i = 0;
		while (i < data.nb_philo)
		{
			if (pthread_mutex_init(&data.forks[i], NULL) != 0)
			{
				printf("❌ Erreur d'initialisation du mutex %d\n", i);
				cleanup_forks(&data);
				continue ;
			}
			i++;
		}
		printf("✅ Initialisation terminée\n");
		// Tests fonctionnels
		test_mutex_operations(&data);
		// Nettoyage
		cleanup_forks(&data);
		printf("✅ Nettoyage terminé\n");
	}
	return (0);
}
 */
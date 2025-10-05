/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 00:50:14 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/05 01:50:12 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*init_threads();

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
			cleanup(philo, i);
			return (NULL);
		}
		philo[i] = str;
		philo[i]->id = i + 1;
		philo[i]->glb_info = data;
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

/* #include <stdio.h> */

/* int main(int ac, char **av)
{
	t_data	*data;
	t_philo	**philo;
	int		i;

	// Parse les arguments
	data = fill_struct(ac, av);
	if (!data)
	{
		printf("Erreur: parsing echoue\n");
		return (1);
	}
	// Teste ta fonction init_philo
	philo = init_philo(data);
	if (!philo)
	{
		printf("Erreur: init_philo echoue\n");
		free(data);
		return (1);
	}
	// Affiche les philosophes crees pour verifier
	printf("=== Test init_philo ===\n");
	printf("Nombre de philosophes: %d\n", data->nb_philo);
	i = 0;
	while (i < data->nb_philo)
	{
		printf("Philo %d:\n", i);
		printf("  - ID: %d\n", philo[i]->id);
		printf("  - glb_info pointe vers data: %s\n",
				(philo[i]->glb_info == data) ? "OUI" : "NON");
		printf("  - last_meal_time: %llu\n", philo[i]->last_meal_time);
		i++;
	}
	// Nettoie la memoire
	cleanup(philo, data->nb_philo);
	free(data);
	printf("Test termine avec succes!\n");
	return (0);
}
 */
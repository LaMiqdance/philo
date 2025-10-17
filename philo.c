/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>           +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:12:06 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/09 00:04:05 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run_simulation(pthread_t *thread_ids, pthread_t monitor_thread,
		int nb_philo)
{
	int	i;

	i = 0;
	pthread_join(monitor_thread, NULL);
	while (i < nb_philo)
	{
		pthread_join(thread_ids[i], NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data		*data;
	pthread_t	*thread_ids;
	pthread_t	monitor_thread;
	t_philo		**philo;

	data = fill_struct(ac, av);
	if (!data)
		return (1);
	printf("done1");
	thread_ids = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!thread_ids)
		return (free(data), 1);
	printf("done2");
	data->forks = init_forks(data);
	if (!data->forks)
		return (free(data), free(thread_ids), 1);
	printf("done3");
	init_data(data);
	printf("done4");
	philo = init_philo(data);
	if (!philo)
		return (free(data), free(thread_ids), free(data->forks), 1);
	printf("done5");
	if (init_threads(thread_ids, philo) == 0)
		return (final_cleanup(philo, data, thread_ids), 1);
	pthread_create(&monitor_thread, NULL, monitor_routine, philo);
	run_simulation(thread_ids, monitor_thread, data->nb_philo);
	final_cleanup(philo, data, thread_ids);
	return (0);
}

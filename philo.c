/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:08:41 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/20 00:17:04 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	run_simulation(pthread_t *thread_ids, pthread_t monitor_thread,
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
	t_data *data;
	pthread_t *thread_ids;
	pthread_t monitor_threads;
	t_philo **philo;

    data = fill_struct(ac, av);
	if (!data)
		return (1); // error msg
    thread_ids = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!thread_ids)
		return (free(data), 1);
    data->forks = init_forks(data); // cleanup_n_exit
	if (!data->forks)
		return (free(data), free(thread_ids), 1); // c;eanup_n_exot
	philo = init_philos(data);
	if (!philo)
		return (free(data), free(thread_ids), free(data->forks), 1);
	if (!init_threads(thread_ids, philo))
		return (final_cleanup(philo, data, thread_ids), 1);
	pthread_create(&monitor_threads, NULL, monitor_routine, philo);
	run_simulation(thread_ids, monitor_threads, data->nb_philo);
	final_cleanup(philo, data, thread_ids);
	return (0);
}


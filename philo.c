/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:08:41 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/19 17:36:22 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_data *data;
	pthread_t *thread_ids;
	pthread_t *monitor_threads;
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
}

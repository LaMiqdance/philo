/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:07:15 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/22 15:05:38 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void	print_status(t_philo *philo, char *message, unsigned long long time)
{
	unsigned long long	current_time;

	current_time = time - philo->glb_data->start_time;
	
	pthread_mutex_lock(&philo->glb_data->m_print);
	printf("%llu %d %s\n", current_time, philo->id, message);
	pthread_mutex_unlock(&philo->glb_data->m_print);
}

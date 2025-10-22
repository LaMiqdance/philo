/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:07:15 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/22 14:38:15 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void	print_status(t_philo *philo, char *message)
{
	unsigned long long	time;

	time = get_current_time_ms();
	
	pthread_mutex_lock(&philo->m_state);
	printf("%d %lld %s", philo->id, time, message);
	pthread_mutex_unlock(&philo->m_state);
}

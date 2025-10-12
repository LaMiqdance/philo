/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:33:13 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/12 19:33:48 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	mutex_print(t_philo *philo)
{
	pthread_mutex_lock(&philo->glb_data->m_print);
	time_print(philo);
	pthread_mutex_unlock(&philo->glb_data->m_print);
}

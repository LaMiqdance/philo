/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:06:31 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/19 15:06:49 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned long long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	while_asleep(t_timer *timing)
{
	unsigned long long	elapsed_time;

	gettimeofday(&timing->current, NULL);
	elapsed_time = timing->current.tv_sec * 1000000 + timing->current.tv_usec
		- timing->start_us;
	while (elapsed_time < timing->target_us)
	{
		gettimeofday(&timing->current, NULL);
		elapsed_time = timing->current.tv_sec * 1000000
			+ timing->current.tv_usec - timing->start_us;
	}
}

void	precise_timing(int ms)
{
	t_timer	timer;

	gettimeofday(&timer.start, NULL);
	timer.start_us = timer.start.tv_sec * 1000000 + timer.start.tv_usec;
	timer.target_us = 1000 * ms;
	if (ms <= 10)
		while_asleep(&timer);
	else if (ms > 10)
	{
		usleep(ms * 750);
		while_asleep(&timer);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>           +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:31:44 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/09 18:05:53 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

char	*print_management(t_philo *philo)
{
	char	*str;

	str = NULL;
	if (philo->has_died == 1)
		str = ft_strdup("has died");
	else if (philo->has_taken_a_fork == 1 && philo->is_eating == 0)
		str = ft_strdup("has taken a fork");
	else if (philo->is_eating == 1)
		str = ft_strdup("is eating");
	else if (philo->is_sleeping == 1)
		str = ft_strdup("is sleeping");
	else if (philo->is_thinking == 1)
		str = ft_strdup("is thinking");
	if (!str)
		return (NULL);
	return (str);
}

void	time_print(t_philo *philo)
{
	unsigned long long	current_time;
	char				*str;

	str = print_management(philo);
	if (!str)
		return ;
	current_time = get_current_time_ms() - philo->glb_data->start_time;
	printf("%lld, %d, %s\n", current_time, philo->id, str);
	free(str);
}

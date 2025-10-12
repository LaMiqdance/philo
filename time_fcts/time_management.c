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
	if (philo->has_taken_a_fork == 1 && philo->is_eating == 0)
		str = ft_strdup("has_taken_a_fork");
	else if (philo->is_eating == 1)
		str = ft_strdup("is_eating");
	else if (philo->is_sleeping == 1)
		str = ft_strdup("is_sleeping");
	else if (philo->is_thinking == 1)
		str = ft_strdup("is_thinking");
	if (!str)
		return (NULL);
	return (str);
}

void	time_print(t_philo *philo)
{
	unsigned long long	time;
	unsigned long long	current_time;
	char				*str;

	time = philo->glb_data->start_time;
	str = print_management(philo);
	if (!str)
		return ;
	current_time = get_current_time_ms() - philo->glb_data->start_time;
	printf("%lld, %d, %s", current_time, philo->id, str);
	free(str);
}


/* // Fonction utilitaire pour obtenir le temps en microsecondes
unsigned long long	get_time_microseconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}
void	test_precision(int ms, const char *description)
{
	unsigned long long	start;
	unsigned long long	end;
	long long			error;

	printf("Test: %s (%d ms)\n", description, ms);
	start = get_time_microseconds();
	precise_timing(ms);
	end = get_time_microseconds();
	unsigned long long actual_time = (end - start) / 1000; // Convertir en ms
	error = actual_time - ms;
	printf("  Temps demandé: %d ms\n", ms);
	printf("  Temps réel: %llu ms\n", actual_time);
	printf("  Erreur: %lld ms\n", error);
	if (error >= -1 && error <= 1)
		printf("  ✅ Précision excellente!\n");
	else if (error >= -5 && error <= 5)
		printf("  ⚠️  Précision acceptable\n");
	else
		printf("  ❌ Précision insuffisante\n");
	printf("\n");
}

int	main(void)
{
	unsigned long long	total_start;
	unsigned long long	total_end;
	unsigned long long	total_time;

	printf("=== TESTS DE PRÉCISION POUR precise_timing ===\n\n");
	// Tests sur différentes durées
	test_precision(5, "Très court (busy-wait direct)");
	test_precision(10, "Seuil limite");
	test_precision(50, "Court (stratégie hybride)");
	test_precision(100, "Moyen");
	test_precision(200, "Long (temps de repas typique)");
	test_precision(500, "Très long");
	// Tests de cohérence - plusieurs appels successifs
	printf("=== TEST DE COHÉRENCE (5 appels de 100ms) ===\n");
	total_start = get_time_microseconds();
	for (int i = 0; i < 5; i++)
	{
		printf("Appel %d... ", i + 1);
		fflush(stdout);
		precise_timing(100);
		printf("OK\n");
	}
	total_end = get_time_microseconds();
	total_time = (total_end - total_start) / 1000;
	printf("Temps total: %llu ms (attendu: 500 ms)\n", total_time);
	printf("Erreur cumulative: %lld ms\n", (long long)total_time - 500);
	return (0);
}
 */
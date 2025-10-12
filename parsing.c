/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:09:35 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/13 01:47:57 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (sign * nb);
}

int	range_check(int i, int index)
{
	if (index == 0)
	{
		if (i < 1 || i > 200)
			return (0);
		return (1);
	}
	else if (index > 0 && index <= 3)
	{
		if (i < 60 || i > 2147483647)
			return (0);
		return (1);
	}
	else if (index == 4)
	{
		if (i < 1 || i > 2147483647)
			return (0);
		return (1);
	}
	else
		return (0);
}

int	is_nbr(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	is_positive(char *str)
{
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			return (0);
		else if (!is_nbr(&str[1]))
			return (0);
	}
	else if (!is_nbr(str))
		return (0);
	return (1);
}

int	*parse_args(int ac, char **args)
{
	int	i;
	int	j;
	int	*tab;

	i = 1;
	tab = malloc(sizeof(int) * ac - 1);
	if (!tab)
		return (NULL);
	if (ac == 5 || ac == 6)
	{
		j = i - 1;
		while (i < ac)
		{
			if (!is_nbr(args[i]) || !is_positive(args[i]))
				return (free(tab), NULL);
			tab[j] = ft_atoi(args[i]);
			i++;
			j++;
		}
		j = 0;
		while (j < ac - 1)
		{
			if (range_check(tab[j], j) == 0)
				return (free(tab), NULL);
			j++;
		}
		return (tab);
	}
	return (free(tab), NULL);
}

t_data	*fill_struct(int ac, char **av)
{
	t_data	*parsed;
	int		*tab;

	parsed = malloc(sizeof(t_data));
	if (!parsed)
		return (NULL);
	tab = parse_args(ac, av);
	if (!tab)
		return (free(parsed), NULL);
	parsed->nb_philo = tab[0];
	parsed->time_to_die = tab[1];
	parsed->time_to_eat = tab[2];
	parsed->time_to_sleep = tab[3];
	parsed->time_to_think = (parsed->time_to_die - parsed->time_to_eat 
        - parsed->time_to_sleep) / 2;
	if (parsed->time_to_think < 0)
    	parsed->time_to_think = 0;
	if (ac == 6)
		parsed->nb_meals = tab[4];
	else
		parsed->nb_meals = -1;
	return (free(tab), parsed);
}

/* void    cleanup(int *tab, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(tab[i]);
		i++;
	}
} */
/* void print_data(t_data *data)
{
	if (!data)
	{
		printf("❌ Erreur: data est NULL\n");
		return ;
	}
	printf("✅ Parsing réussi:\n");
	printf("   - Nombre de philosophes: %d\n", data->nb_philo);
	printf("   - Time to die: %d ms\n", data->time_to_die);
	printf("   - Time to eat: %d ms\n", data->time_to_eat);
	printf("   - Time to sleep: %d ms\n", data->time_to_sleep);
	if (data->nb_meals == -1)
		printf("   - Nombre de repas: illimité\n");
	else
		printf("   - Nombre de repas: %d\n", data->nb_meals);
}

void	test_case(char *description, int argc, char **argv)
{
	t_data	*result;

	printf("\n🧪 Test: %s\n", description);
	printf("   Commande: ./philo");
	for (int i = 1; i < argc; i++)
		printf(" %s", argv[i]);
	printf("\n");
	result = fill_struct(argc, argv);
	if (result)
	{
		print_data(result);
		free(result);
	}
	else
	{
		printf("❌ Parsing échoué\n");
	}
}

int	main(void)
{
	printf("=== TESTS DU PARSING PHILOSOPHERS ===\n");

	// Test 1: Arguments valides basiques
	char *args1[] = {"./philo", "4", "410", "200", "200"};
	test_case("Arguments valides basiques", 5, args1);

	// Test 2: Avec paramètre optionnel
	char *args2[] = {"./philo", "5", "800", "200", "200", "7"};
	test_case("Avec nombre de repas", 6, args2);

	// Test 3: Un seul philosophe
	char *args3[] = {"./philo", "1", "800", "200", "200"};
	test_case("Un seul philosophe", 5, args3);

	// Test 4: Maximum de philosophes
	char *args4[] = {"./philo", "200", "800", "200", "200"};
	test_case("Maximum de philosophes", 5, args4);

	// Test 5: Temps minimum
	char *args5[] = {"./philo", "5", "60", "60", "60"};
	test_case("Temps minimum", 5, args5);

	// Tests d'erreur
	printf("\n=== TESTS D'ERREURS ===\n");

	// Test 6: Trop peu d'arguments
	char *args6[] = {"./philo", "4", "410", "200"};
	test_case("Trop peu d'arguments", 4, args6);

	// Test 7: Nombre négatif
	char *args7[] = {"./philo", "-4", "410", "200", "200"};
	test_case("Nombre négatif", 5, args7);

	// Test 8: Caractères non numériques
	char *args8[] = {"./philo", "4", "abc", "200", "200"};
	test_case("Caractères non numériques", 5, args8);

	// Test 9: Zéro philosophe
	char *args9[] = {"./philo", "0", "410", "200", "200"};
	test_case("Zéro philosophe", 5, args9);

	// Test 10: Trop de philosophes
	char *args10[] = {"./philo", "201", "410", "200", "200"};
	test_case("Trop de philosophes", 5, args10);

	// Test 11: Temps trop court
	char *args11[] = {"./philo", "4", "59", "200", "200"};
	test_case("Temps trop court", 5, args11);

	// Test 12: Avec signe plus
	char *args12[] = {"./philo", "+4", "+410", "+200", "+200"};
	test_case("Avec signes plus", 5, args12);

	printf("\n=== FIN DES TESTS ===\n");
	return (0);
} */
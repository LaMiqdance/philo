#include "philo.h"

int	range_check(int i, int index)
{
	if (index == 0)
	{
		if (i < 1 || i > 200)
		{
			/* write(1, "wrong number of philosophers,
				should range between 1 and 200", 59); */
			return (0);
		}
		return (1);
	}
	else if (index > 0 && index <= 3)
	{
		if (i < 1 || i > 2147483647)
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
	if (ac == 6)
		parsed->number_of_times_each_philosopher_must_eat = tab[4];
	else
		parsed->number_of_times_each_philosopher_must_eat = 0;
	return (free(tab), parsed);
}

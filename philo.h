#ifndef PHILO_H
# define PHILO_H

#include <sys/time.h>

typedef struct  s_data
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_meals;
}               t_data;


// parsing
int is_nbr(char *str);
int is_positive(char *str);
int	ft_atoi(const char *str);
int range_check(int i, int index);
int *parse_args(int ac, char **args);

#endif
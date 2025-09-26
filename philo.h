#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
/* # include <stdio.h> */
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_meals;
	pthread_mutex_t		*forks;
}						t_data;

typedef struct s_timer
{
	struct timeval		start;
	struct timeval		current;
	unsigned long long	start_us;
	unsigned long long	current_us;
	unsigned long long	target_us;
}						t_timer;

typedef struct s_philo
{
	int					id;
	t_data				*glb_info;
	unsigned long long	last_meal_time;
}						t_philo;

// parsing
int						is_nbr(char *str);
int						is_positive(char *str);
int						ft_atoi(const char *str);
int						range_check(int i, int index);
int						*parse_args(int ac, char **args);

// time management
unsigned long long		get_current_time_mms(void);

// nap time management
void					while_asleep(t_timer *timing);
void					precise_sleep(int ms);

#endif
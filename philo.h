/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>           +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 01:26:50 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/09 18:06:28 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* typedef enum e_state_type
{
	STATE_EATING,
	STATE_SLEEPING,
	STATE_THINKING,
	STATE_FORK,
}						t_state_type; */

typedef struct s_data
{
	int					nb_philo;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	number_of_times_each_philosopher_must_eat;
	unsigned long long	time_to_think;
	int					simu_stop;
	unsigned long long	start_time;
	pthread_mutex_t		m_simu_stop;
	pthread_mutex_t		m_print;
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
	int					is_thinking;
	int					has_taken_a_fork;
	int					is_eating;
	int					is_sleeping;
	int					has_died;
	pthread_mutex_t		m_state;
	unsigned long long	meals_eaten;
	t_data				*glb_data;
	pthread_mutex_t		m_last_meal_time;
	unsigned long long	last_meal_time;
}						t_philo;

// parsing
int						is_nbr(char *str);
int						is_positive(char *str);
int						range_check(int i, int index);
int						*parse_args(int ac, char **args);
t_data					*fill_struct(int ac, char **av);

// init
int						init_threads(pthread_t *threads_ids, t_philo **philo);
pthread_mutex_t			*init_forks(t_data *data);
t_philo					**init_philo(t_data *data);

// init_utils
int						init_data(t_data *data);
void					init_states(t_philo *philo);
t_philo					*fill_philo_subpart(t_data *data, int i);

// time management
unsigned long long		get_current_time_ms(void);

// nap time management
void					while_asleep(t_timer *timing);
void					precise_timing(int ms);
char					*print_management(t_philo *philo);
void					time_print(t_philo *philo);

// philo_routine
void					*philosopher_routine(void *arg);

// lock
int						lock_fork(t_philo *philo);

// unlock
void					unlock_fork(t_philo *philo);

// routine_utils
void					lock_last_meal_time(t_philo *philo);
void					mutex_print(t_philo *philo);

// routine_monitor
void					*monitor_routine(void *arg);

// cleanup
void					cleanup_philos(t_philo **philo, int index, int mutex);
void					cleanup_mutex(pthread_mutex_t *mutex, int index);
void					final_cleanup(t_philo **philo, t_data *data,
							pthread_t *thread_ids);

// utils
int						ft_strlen(char *str);
char					*ft_strdup(char *s);
int						ft_atoi(const char *str);

#endif
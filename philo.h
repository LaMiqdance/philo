/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:04:17 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/19 23:24:53 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int					nb_philo;
	int					number_of_times_each_philosopher_must_eat;
	int					simu_stop;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	start_time;
	pthread_mutex_t		m_simu_stop;
	pthread_mutex_t		m_print;
	pthread_mutex_t		*forks;
}						t_data;

typedef struct s_philo
{
	int					id;
	int					has_taken_a_fork;
	int					is_eating;
	int					is_thinking;
	int					is_sleeping;
	int					meals_eaten;
	unsigned long long	last_meal_time;
	int					has_died;

	pthread_mutex_t		m_has_taken_a_fork;
	pthread_mutex_t		m_is_eating;
	pthread_mutex_t		m_is_thinking;
	pthread_mutex_t		m_is_sleeping;
	pthread_mutex_t		m_has_died;
	pthread_mutex_t		m_last_meal_time;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		m_meals_eaten;
	t_data				*glb_data;
}						t_philo;

typedef struct s_timer
{
	struct timeval		start;
	struct timeval		current;
	unsigned long long	start_us;
	unsigned long long	current_us;
	unsigned long long	target_us;
}						t_timer;

// parsing
t_data	*fill_struct(int ac, char **av);
int		*parse_args(int ac, char **args);
int		is_positive(char *str);
int		is_nbr(char *str);
int		range_check(int i, int index);

// init
int						init_threads(pthread_t *threads_ids, t_philo **philo);
int						init_data(t_data *data);
void					init_states(t_philo *philo);
pthread_mutex_t			*init_forks(t_data *data);
t_philo					**init_philos(t_data *data);
t_philo					*fill_philo_subpart(t_data *data, int i);

// routine
void					*monitor_routine(void *arg);

// cleanup
void	cleanup_philos(t_philo **philo, int index);
void	cleanup_mutex(pthread_mutex_t *mutex, int index);
void	final_cleanup(t_philo **philo, t_data *data, pthread_t *thread_ids);

#endif
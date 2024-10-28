/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:35:19 by dosokin           #+#    #+#             */
/*   Updated: 2024/01/29 11:25:33 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ERROR 1

typedef enum e_error
{
	SYNTAX_ERR,
	ARG_NBR,
	NO_UINT,
	MEM_ERR,
	ZERO_PHILO,
	THR_ISSUE,
	MAX_THR,
	MUTEX,
	INT_OVERFLOW,
}								t_err;

enum							e_philo_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD
};

typedef enum e_fork_state
{
	UNAVAILABLE,
	AVAILABLE,
}								t_fork_state;

typedef struct s_fork
{
	t_fork_state				*fork_status;
	pthread_mutex_t				*mutex;
}								t_fork;

struct							s_timer
{
	struct timeval				*time;
	pthread_mutex_t				*mutex;
};

struct							s_end
{
	bool						is_death;
	bool						everyone_ate;
	pthread_mutex_t				*mutex;
};

struct							s_protected_bool
{
	bool						boolean;
	pthread_mutex_t				*mutex;
};

struct	s_philosophers_tab;

typedef struct s_main_data
{
	size_t						number_of_philosophers;
	size_t						time_to_die;
	size_t						time_to_eat;
	size_t						time_to_sleep;
	int							must_eat;

	unsigned long int			ref_time;
	pthread_mutex_t				*print_mutex;
	struct s_philosophers_tab	*philosophers;
	pthread_t					supervision_thread;

}								t_main_data;

typedef struct s_philosophers_tab
{
	size_t						id;
	pthread_t					thread;
	pthread_mutex_t				*left_fork;
	pthread_mutex_t				*right_fork;
	unsigned long int			last_meal;
	enum e_philo_state			state;
	bool						first_meal;

	struct s_protected_bool		satiated;
	struct s_protected_bool		dead;
	struct s_protected_bool		end;

	struct s_main_data			data;

}								t_philo;

int								ft_safe_atoi(char *s, bool *error);
int								error_manager(t_err error_type);

unsigned int					get_time_in_ms(unsigned long int ref_time);
void							ft_printf(t_philo philo,
									enum e_philo_state state);

int								initialize_data(t_main_data *data);

int								launch_philos_threads(t_main_data *data);
int								join_philos_threads(t_main_data *data);

pthread_mutex_t					*init_mutex(void);
int								clear_mutex(pthread_mutex_t **mutex);

void							clear_philo_tab(t_philo **philo_tab,
									size_t philo_count);
void							clear_data(t_main_data *data);

void							*philo_routine(void *arg);

void							*supervision(void *arg);

void							release_forks(t_philo *philo);
int								take_forks(t_philo *philo);

int								extract_args(int argc, char **argv,
									t_main_data *data);
int								check_args_validity(t_main_data data);

bool							check_for_end(t_philo *philo);
void							update_state(t_philo *philo,
									enum e_philo_state state);
bool							is_dead(t_philo *philo);
int								ft_sleep(t_philo *philo,
									unsigned long int time);

// t_philo		             *ft_philo_new(t_philo *head);

#endif

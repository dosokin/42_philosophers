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
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_error
{
	ARG_NBR,
	NO_UINT,
	MEM_ISSUE,
	ZERO_PHILO,
	THR_ISSUE,
	MAX_THR,
	MUTEX,
}							t_err;

typedef enum e_philo_state
{
	HESDEAD,
	EATIN,
	SLEEPIN,
	THINKIN,
}							t_philo_state;

typedef enum e_fork_state
{
	UNAVAILABLE,
	AVAILABLE,
}							t_fork_state;

typedef struct s_fork
{
	t_fork_state			*fork_status;
	pthread_mutex_t			*mutex;
}							t_fork;

typedef struct s_philosophers
{
	struct s_philosophers	*last;
	int						philosopher_id;
	pthread_t				thread;
	t_fork					*left_fork;
	t_fork					*right_fork;
	struct timeval			*last_meal;
	t_philo_state			philo_state;
	struct s_philosophers	*next;
	struct s_parameters		*prm;
}							t_philo;

typedef struct s_timer
{
	struct timeval			*time_reference;
	pthread_mutex_t			*time_mutex;
}t_time;

typedef struct s_hesdead
{
	int						someone_died;
	pthread_mutex_t			*dead_mutex;
}t_hesdead;

typedef struct s_parameters
{
	int						number_of_philosophers;
	float					time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat;
	t_hesdead				*dead;
	t_time					*ttime;
	t_philo					**philosophers;
}							t_par;

int							ft_atoui_safe(const char *nptr, int *flag_error);
int							error_manager(t_err error);
float						get_time(t_time *ttime);
t_philo						**init_philosophers(t_par *parameters);
t_par						*arg_manager(int argc, char **argv,
								struct timeval *reference);
float						get_chrono(struct timeval *reference);
void						deinit(t_par *parameters, int philo_number);
int							philosopher_eating(t_philo *philosophers);
int							take_forks(t_philo *philosophers);
int							philosopher_thinking(t_philo *philosophers);
void						do_something(t_philo *philosophers, int repetition,
								int act_time);
int							philosopher_sleeping(t_philo *philosophers);
void						*lock_forks(void *void_fork_mutex);
void						*unlock_forks(void *void_fork_mutex);
void						*routine(void *arg);
int							rejoin_threads(t_par *parameters);
int							create_threads(t_par *parameters);
int							is_dead(t_philo *philosophers);

#endif

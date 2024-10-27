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
# include <stdbool.h>

#define ERROR 1

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
}							t_err;

enum e_philo_state
{
	DEAD,
	EAT,
	SLEEP,
	THINK,
    FORK,
};

enum e_philo_action
{
    TAKE_FORK,
    EATING,
    SLEEPING,
    THINKING,
    DYING,
};

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

struct s_timer
{
	struct timeval			*time;
	pthread_mutex_t			*mutex;
};

struct s_death
{
	bool						is_death;
	pthread_mutex_t			    *mutex;
};

struct s_philosophers_tab;

typedef struct s_main_data
{
	size_t						number_of_philosophers;
	size_t					    time_to_die;
	size_t						time_to_eat;
	size_t						time_to_sleep;
	int						    must_eat;
	struct s_death				death;
	struct timeval				ref_time;
    pthread_mutex_t			    *print_mutex;
    struct s_philosophers_tab   *philosophers;
}t_main_data;

typedef struct s_philosophers_tab
{
    size_t					id;
    pthread_t				thread;
    pthread_mutex_t			*left_fork;
    pthread_mutex_t			*right_fork;
    struct timeval			last_meal;
    enum e_philo_state		state;

    struct s_main_data      main_data;
} t_philo;

//
//int							ft_atoui_safe(const char *nptr, int *flag_error);
//int							error_manager(t_err error);
//float						get_time(t_time *time);
//t_philo						**init_philosophers(t_par *parameters);
//t_par						*arg_manager(int argc, char **argv,
//								struct timeval *reference);
//float						get_chrono(struct timeval *reference);
//void						deinit(t_par *parameters, int philo_number);
//int							philosopher_eating(t_philo *philosophers);
//int							take_forks(t_philo *philosophers);
//int							philosopher_thinking(t_philo *philosophers);
//void						do_something(t_philo *philosophers, int repetition,
//								int act_time);
//int							philosopher_sleeping(t_philo *philosophers);
//void						*lock_forks(void *void_fork_mutex);
//void						*unlock_forks(void *void_fork_mutex);
//void						*routine(void *arg);
//int							rejoin_threads(t_par *parameters);
//int							create_threads(t_par *parameters);
//int							is_dead(t_philo *philosophers);

int                         ft_safe_atoi(char *s, bool *error);
int	                        error_manager(t_err error_type);

unsigned int                get_time_in_ms();

int                         initialize_data(t_main_data *data);

int	                        launch_philos_threads(t_main_data *data);
int	                        join_philos_threads(t_main_data *data);

pthread_mutex_t             *init_mutex();
int                         clear_mutex(pthread_mutex_t **mutex);

void                        clear_philo_tab(t_philo **philo_tab, size_t philo_count);
void                        clear_data(t_main_data *data);

//TODO=REMOVE
void	                    *test_routine(void *arg);
void                        *routine(void *arg);


//t_philo	                *ft_philo_new(t_philo *head);


#endif

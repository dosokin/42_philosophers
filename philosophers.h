/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:35:19 by dosokin           #+#    #+#             */
/*   Updated: 2024/01/24 10:35:21 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#   define PHILOSOPHERS_H

#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>

typedef enum e_error{
    ARG_NBR,
    NO_UINT,
    MEM_ISSUE,
    ZERO_PHILO,
    THR_ISSUE,
    MAX_THR,
    MUTEX,
}t_err;

typedef enum e_philo_state{
    HESDEAD,
    EATIN,
    SLEEPIN,
    THINKIN,
}t_philo_state;

typedef enum e_fork_state{
    UNAVAILABLE,
    AVAILABLE,
}t_fork_state;

typedef struct s_fork{
    t_fork_state *fork_status;
    pthread_mutex_t *mutex;
}t_fork;

typedef struct s_philosophers{
    struct s_philosophers *last;
    int philosopher_id;
    pthread_t thread;
    t_fork *left_fork;
    t_fork *right_fork;
    struct timeval *last_meal;
    t_philo_state philo_state;
    struct s_philosophers *next;
    struct s_parameters *prm;
}t_philo;

typedef struct s_parameters{
    int number_of_philosophers;
    float time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
    int someone_died;
    t_philo	**philosophers;
    struct timeval *time_reference;
}t_par;

int	ft_atoui_safe(const char *nptr, int *flag_error);

#endif
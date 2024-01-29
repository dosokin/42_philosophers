/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:00:18 by dosokin           #+#    #+#             */
/*   Updated: 2024/01/29 12:38:22 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_fork	*init_fork(void)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->fork_status = malloc(sizeof(t_fork_state));
	if (!fork->fork_status)
		return (NULL);
	*(fork->fork_status) = AVAILABLE;
	fork->mutex = malloc(sizeof(pthread_mutex_t));
	if (!fork->mutex)
		return (NULL);
	pthread_mutex_init(fork->mutex, NULL);
	return (fork);
}

static void	philosopher_recave(t_philo **philosophers, t_par *parameters, int i)
{
	struct timeval	*timeref;

	timeref = parameters->ttime->time_reference;
	philosophers[i]->philosopher_id = i + 1;
	philosophers[i]->right_fork = init_fork();
	if (philosophers[i]->last)
	{
		philosophers[i]->last->next = philosophers[i];
		philosophers[i]->left_fork = philosophers[i]->last->right_fork;
	}
	philosophers[i]->last_meal = malloc(sizeof(struct timeval));
	philosophers[i]->prm = parameters;
	philosophers[i]->last_meal->tv_sec = timeref->tv_sec;
	philosophers[i]->last_meal->tv_usec = timeref->tv_usec;
}

t_philo	**init_philosophers(t_par *parameters)
{
	int		i;
	t_philo	**philosophers;
	t_philo	*last_philosopher;

	i = 0;
	philosophers = malloc(parameters->number_of_philosophers
			* sizeof(t_philo *));
	last_philosopher = NULL;
	while (i < parameters->number_of_philosophers)
	{
		philosophers[i] = malloc(sizeof(t_philo));
		if (!philosophers[i])
			return (NULL);
		philosophers[i]->last = last_philosopher;
		philosopher_recave(philosophers, parameters, i);
		last_philosopher = philosophers[i];
		i++;
	}
	philosophers[--i]->next = philosophers[0];
	philosophers[0]->last = philosophers[i];
	philosophers[0]->left_fork = philosophers[i]->right_fork;
	return (philosophers);
}

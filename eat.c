/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:00:18 by dosokin           #+#    #+#             */
/*   Updated: 2024/01/28 16:47:36 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	take_first_fork(t_philo *philosophers)
{
	lock_forks(philosophers->left_fork->mutex);
	if (*(philosophers->left_fork->fork_status))
	{
		*(philosophers->left_fork->fork_status) = UNAVAILABLE;
		unlock_forks(philosophers->left_fork->mutex);
		pthread_mutex_lock(philosophers->prm->ttime->time_mutex);
		printf("%f %d has taken a fork\n", get_time(philosophers->prm->ttime),
			philosophers->philosopher_id);
		pthread_mutex_unlock(philosophers->prm->ttime->time_mutex);
		return (1);
	}
	else
	{
		unlock_forks(philosophers->left_fork->mutex);
		return (0);
	}
}

static int	take_second_fork(t_philo *philosophers)
{
	lock_forks(philosophers->right_fork->mutex);
	if (*(philosophers->right_fork->fork_status))
	{
		*(philosophers->right_fork->fork_status) = UNAVAILABLE;
		unlock_forks(philosophers->right_fork->mutex);
		pthread_mutex_lock(philosophers->prm->ttime->time_mutex);
		printf("%f %d has taken a fork\n", get_time(philosophers->prm->ttime),
			philosophers->philosopher_id);
		pthread_mutex_unlock(philosophers->prm->ttime->time_mutex);
		return (1);
	}
	else
	{
		unlock_forks(philosophers->right_fork->mutex);
		lock_forks(philosophers->left_fork->mutex);
		*(philosophers->left_fork->fork_status) = AVAILABLE;
		unlock_forks(philosophers->left_fork->mutex);
		return (0);
	}
}

int	take_forks(t_philo *philosophers)
{
	if (take_first_fork(philosophers) == 0)
		return (0);
	return (take_second_fork(philosophers));
}

static void	release_forks(t_philo *philosophers)
{
	lock_forks(philosophers->left_fork->mutex);
	*(philosophers->left_fork->fork_status) = AVAILABLE;
	unlock_forks(philosophers->left_fork->mutex);
	lock_forks(philosophers->right_fork->mutex);
	*(philosophers->right_fork->fork_status) = AVAILABLE;
	unlock_forks(philosophers->right_fork->mutex);
}

int	philosopher_eating(t_philo *philosophers)
{
	int	eat_repetition;

	eat_repetition = philosophers->prm->time_to_eat / 8;
	gettimeofday(philosophers->last_meal, NULL);
	pthread_mutex_lock(philosophers->prm->ttime->time_mutex);
	printf("%f %d is eating\n", get_time(philosophers->prm->ttime),
		philosophers->philosopher_id);
	pthread_mutex_unlock(philosophers->prm->ttime->time_mutex);
	do_something(philosophers, eat_repetition, philosophers->prm->time_to_eat);
	release_forks(philosophers);
	return (1);
}

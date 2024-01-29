/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lockers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:00:18 by dosokin           #+#    #+#             */
/*   Updated: 2024/01/29 12:37:41 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*lock_forks(void *void_fork_mutex)
{
	pthread_mutex_t	*fork_mutex;

	fork_mutex = (pthread_mutex_t *)void_fork_mutex;
	pthread_mutex_lock(fork_mutex);
	return (NULL);
}

void	*unlock_forks(void *void_fork_mutex)
{
	pthread_mutex_t	*fork_mutex;

	fork_mutex = (pthread_mutex_t *)void_fork_mutex;
	pthread_mutex_unlock(fork_mutex);
	return (NULL);
}

int	is_dead(t_philo *philosophers)
{
	pthread_mutex_lock(philosophers->prm->dead->dead_mutex);
	if (philosophers->prm->dead->someone_died > 0)
	{
		pthread_mutex_unlock(philosophers->prm->dead->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(philosophers->prm->dead->dead_mutex);
	return (0);
}

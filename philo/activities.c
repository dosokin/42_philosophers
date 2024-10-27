/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:00:18 by dosokin           #+#    #+#             */
/*   Updated: 2024/01/29 12:57:11 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_chrono(t_philo *philosophers, int time_to_die)
{
	float	chrono;

	chrono = get_chrono(philosophers->prev_meal);
	if (chrono > time_to_die)
	{
		pthread_mutex_lock(philosophers->main->time->mutex);
		printf("%f %d died\n", get_time(philosophers->main->time),
			philosophers->id);
		pthread_mutex_unlock(philosophers->main->time->mutex);
		pthread_mutex_lock(philosophers->main->dead->mutex);
		++philosophers->main->dead->is_any_death;
		pthread_mutex_unlock(philosophers->main->dead->mutex);
		return (1);
	}
	return (0);
}

int	philosopher_thinking(t_philo *philosophers)
{
	int	time_to_die;

	time_to_die = philosophers->main->time_to_die;
	pthread_mutex_lock(philosophers->main->time->mutex);
	printf("%f %d is thinking\n", get_time(philosophers->main->time),
		philosophers->id);
	pthread_mutex_unlock(philosophers->main->time->mutex);
	while (1)
	{
		if (is_dead(philosophers) == 1)
			return (0);
		if (check_chrono(philosophers, time_to_die) == 1)
			return (0);
		if (take_forks(philosophers) == 1)
			break ;
		else
			usleep(30);
	}
	return (1);
}

void	do_something(t_philo *philosophers, int repetition, int act_time)
{
	int				time;
	struct timeval	reference;
	float			still;
	int				time_to_die;

	time_to_die = philosophers->main->time_to_die;
	gettimeofday(&reference, NULL);
	time = 0;
	while (++time <= repetition)
	{
		usleep(7750);
		if (check_chrono(philosophers, time_to_die) == 1)
			return ;
	}
	still = ((float)(act_time) - (float)get_chrono(&reference));
	if (still > 0)
		usleep(still * 1000);
}

int	philosopher_sleeping(t_philo *philosophers)
{
	int	sleep_repetition;

	sleep_repetition = philosophers->main->time_to_sleep / 8;
	pthread_mutex_lock(philosophers->main->time->mutex);
	printf("%f %d is sleeping\n", get_time(philosophers->main->time),
		philosophers->id);
	pthread_mutex_unlock(philosophers->main->time->mutex);
	do_something(philosophers, sleep_repetition,
		philosophers->main->time_to_sleep);
	return (1);
}

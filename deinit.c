/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:00:18 by dosokin           #+#    #+#             */
/*   Updated: 2024/01/28 16:47:29 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	deinit_philosophers(t_philo *philosopher)
{
	free(philosopher->right_fork->fork_status);
	pthread_mutex_destroy(philosopher->right_fork->mutex);
	free(philosopher->right_fork->mutex);
	free(philosopher->right_fork);
	free(philosopher->last_meal);
	free(philosopher);
}

void	deinit(t_par *parameters, int philo_number)
{
	int	i;

	i = 0;
	while (i < philo_number)
	{
		deinit_philosophers(parameters->philosophers[i]);
		i++;
	}
	free(parameters->philosophers);
	free(parameters->ttime->time_reference);
	pthread_mutex_destroy(parameters->ttime->time_mutex);
	free(parameters->ttime->time_mutex);
	free(parameters->ttime);
	pthread_mutex_destroy(parameters->dead->dead_mutex);
	free(parameters->dead->dead_mutex);
	free(parameters->dead);
	free(parameters);
}

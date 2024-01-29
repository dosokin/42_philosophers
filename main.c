/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:00:18 by dosokin           #+#    #+#             */
/*   Updated: 2024/01/29 11:25:55 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	freeze(t_philo *philosophers)
{
	int	impair;

	impair = 0;
	if (philosophers->prm->number_of_philosophers % 2 == 0)
	{
		if (philosophers->philosopher_id % 2 == 0)
			usleep(50);
	}
	else
	{
		impair = 1;
		if (philosophers->philosopher_id % 3 == 0)
			impair = 1;
		else if (philosophers->philosopher_id % 3 == 1)
			usleep(philosophers->prm->time_to_eat * 980
				- philosophers->philosopher_id);
		else if (philosophers->philosopher_id % 3 == 2)
			usleep(philosophers->prm->time_to_eat
				+ philosophers->prm->time_to_sleep * 980
				- philosophers->philosopher_id);
	}
	return (impair);
}

static int	daily_routine(t_philo *philosophers, int must_eat, int eat_time)
{
	philosopher_thinking(philosophers);
	if (is_dead(philosophers) == 1)
		return (1);
	philosopher_eating(philosophers);
	if (is_dead(philosophers) == 1)
		return (1);
	if (must_eat)
	{
		if (eat_time >= must_eat)
			return (1);
	}
	philosopher_sleeping(philosophers);
	if (is_dead(philosophers) == 1)
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philosophers;
	int		impair;
	int		must_eat;
	int		eat_time;

	eat_time = 0;
	philosophers = (t_philo *)arg;
	must_eat = philosophers->prm->must_eat;
	impair = freeze(philosophers);
	while (1)
	{
		if (impair)
			usleep(100);
		eat_time++;
		if (daily_routine(philosophers, must_eat, eat_time) == 1)
			break ;
	}
	return (philosophers);
}

int	main(int argc, char **argv)
{
	t_par			*parameters;
	struct timeval	*reference;

	reference = malloc(sizeof(struct timeval));
	gettimeofday(reference, NULL);
	parameters = arg_manager(argc, argv, reference);
	if (!parameters)
		return (-1);
	if (create_threads(parameters) == -1)
		return (-1);
	if (rejoin_threads(parameters) == -1)
		return (-1);
	deinit(parameters, parameters->number_of_philosophers);
	return (1);
}

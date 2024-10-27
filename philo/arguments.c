/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:00:18 by dosokin           #+#    #+#             */
/*   Updated: 2024/01/29 12:37:27 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	conventional_checks(t_par *parameters)
{
	if (parameters->number_of_philosophers == 0)
	{
		free(parameters);
		return (error_manager(ZERO_PHILO));
	}
	if (parameters->number_of_philosophers > 32753)
	{
		free(parameters);
		return (error_manager(MAX_THR));
	}
	return (1);
}

static int	primary_checks(int argc, char **argv)
{
	int	i;
	int	y;

	if (argc != 5 && argc != 6)
		return (error_manager(ARG_NBR));
	i = 1;
	while (i < argc)
	{
		y = 0;
		while (argv[i][y])
		{
			if (y == 0 && (argv[i][y] == '-' || argv[i][y] == '+'))
				y++;
			else if (!(argv[i][y] <= '9' && argv[i][y] >= '0'))
				return (error_manager(ARG_NBR));
			else
				y++;
		}
		if (y == 0)
			return (error_manager(NO_UINT));
		i++;
	}
	return (1);
}

static int	arguments_to_delays(t_par *parameters, int argc, char **argv)
{
	int	flag_error;

	flag_error = 1;
	parameters->number_of_philosophers = ft_atoui_safe(argv[1], &flag_error);
	parameters->time_to_die = ft_atoui_safe(argv[2], &flag_error);
	parameters->time_to_eat = ft_atoui_safe(argv[3], &flag_error);
	parameters->time_to_sleep = ft_atoui_safe(argv[4], &flag_error);
	if (argc == 6)
		parameters->must_eat = ft_atoui_safe(argv[5], &flag_error);
	else
		parameters->must_eat = 0;
	if (flag_error == -1)
		return (-1);
	return (1);
}

static void	mutex_inits(t_par *parameters)
{
	parameters->dead->mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(parameters->dead->mutex, NULL);
	parameters->time->mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(parameters->time->mutex, NULL);
}

t_par	*arg_manager(int argc, char **argv, struct timeval *reference)
{
	t_par	*parameters;

	if (primary_checks(argc, argv) == -1)
		return (NULL);
	parameters = malloc(sizeof(t_par));
	if (!parameters)
	{
		error_manager(MEM_ERR);
		return (NULL);
	}
	if (arguments_to_delays(parameters, argc, argv) == -1)
	{
		free(parameters);
		error_manager(NO_UINT);
		return (NULL);
	}
	if (conventional_checks(parameters) == -1)
		return (NULL);
	parameters->time = malloc(sizeof(t_time));
	parameters->time->time_reference = reference;
	parameters->philosophers = init_philosophers(parameters);
	parameters->dead = malloc(sizeof(t_hesdead));
	parameters->dead->is_any_death = 0;
	mutex_inits(parameters);
	return (parameters);
}

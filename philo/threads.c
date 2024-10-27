/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:00:18 by dosokin           #+#    #+#             */
/*   Updated: 2024/01/28 19:28:02 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threads(t_par *parameters)
{
	int	i;

	i = 0;
	while (i < parameters->number_of_philosophers)
	{
		if (pthread_create(&(parameters->philosophers[i]->thread), NULL,
				&routine, parameters->philosophers[i]) != 0)
			return (error_manager(THR_ISSUE));
		i++;
	}
	return (1);
}

int	rejoin_threads(t_par *parameters)
{
	int	i;

	i = 0;
	while (i < parameters->number_of_philosophers)
	{
		if (pthread_join(parameters->philosophers[i]->thread, NULL) != 0)
			return (error_manager(THR_ISSUE));
		i++;
	}
	return (1);
}

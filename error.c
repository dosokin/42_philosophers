/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:00:18 by dosokin           #+#    #+#             */
/*   Updated: 2024/01/28 16:47:45 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_manager(t_err error)
{
	if (error == ARG_NBR)
		write(2, "Error\nWrong number of arguments\n", 32);
	else if (error == NO_UINT)
		write(2, "Error\nPlease only use unsigned_ints as arguments", 48);
	else if (error == MEM_ISSUE)
		write(2, "Error\nMemory problem encountred\n", 32);
	else if (error == ZERO_PHILO)
		write(2,
			"Error\nPhilosophers should exist\n", 32);
	else if (error == THR_ISSUE)
		write(2, "Error\nInternal problem creating threads\n", 40);
	else if (error == MAX_THR)
		write(2, "Error\n32753 is the threads limit\n", 33);
	else if (error == MUTEX)
		write(2, "Error\nProblem wiht a mutex\n", 27);
	return (-1);
}

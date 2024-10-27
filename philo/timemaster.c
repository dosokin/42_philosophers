/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timemaster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:00:18 by dosokin           #+#    #+#             */
/*   Updated: 2024/01/28 16:48:40 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

float	get_time(t_time *time)
{
	float			current_time;
	struct timeval	now;

	gettimeofday(&now, NULL);
	current_time = (((now.tv_sec - time->time_reference->tv_sec) * 1000)
			+ ((double)(now.tv_usec - time->time_reference->tv_usec)
				/ (double)1000));
	return (current_time);
}

float	get_chrono(struct timeval *reference)
{
	float			chrono;
	struct timeval	now;

	gettimeofday(&now, NULL);
	chrono = (((now.tv_sec - reference->tv_sec) * 1000) + ((double)(now.tv_usec
					- reference->tv_usec) / (double)1000));
	return (chrono);
}

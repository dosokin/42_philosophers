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

int extract_args(int argc, char **argv, t_main_data *data)
{
    bool error;

    if (argc != 5 && argc != 6)
        return (error_manager(ARG_NBR));
    error = false;
    argv++;
    data->number_of_philosophers = ft_safe_atoi(*argv, &error);
    argv++;
    data->time_to_die = ft_safe_atoi(*argv, &error);
    argv++;
    data->time_to_eat = ft_safe_atoi(*argv, &error);
    argv++;
    data->time_to_sleep = ft_safe_atoi(*argv, &error);
    argv++;
    if (argc == 6)
        data->must_eat = ft_safe_atoi(*argv, &error);
    else
        data->must_eat = -1;
    if (error)
        return (1);
    return (0);
}

int check_args_validity(t_main_data data)
{
    if (!data.number_of_philosophers)
    {
        error_manager(ZERO_PHILO);
        return (1);
    }
    return (0);
}
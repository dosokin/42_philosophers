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

int	main(int argc, char **argv)
{
	t_main_data     data;

    if (extract_args(argc, argv, &data) == ERROR)
        return (EXIT_FAILURE);
    if (check_args_validity(data) == ERROR)
        return (EXIT_FAILURE);
    if (initialize_data(&data) == ERROR)
        return (EXIT_FAILURE);
    if (launch_philos_threads(&data) == ERROR)
		return (EXIT_FAILURE);
	if (join_philos_threads(&data) == ERROR)
		return (EXIT_FAILURE);
    clear_data(&data);
	return (EXIT_SUCCESS);
}

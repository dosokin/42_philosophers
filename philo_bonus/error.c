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
#include <stdbool.h>

static size_t ft_strlen(const char *s)
{
    size_t i;

    if (!s)
        return (0);
    i = 0;
    while (s[i])
        i++;
    return (i);
}

int	error_manager(t_err error_type)
{
    static bool broadcasted = false;
    const char *errors[9] = {
            "invalid syntax",
            "wrong number of arguments",
            "please only use positive ints as arguments",
            "memory problem encountered",
            "philosophers should exist",
            "internal problem creating threads",
            "32753 is the threads limit",
            "problem happened initializing a mutex",
            "int overflow"
    };

    if (broadcasted || error_type > 8)
        return (1);
    broadcasted = true;
    write(2, "Error\n", 6);
    write(2, errors[error_type], ft_strlen(errors[error_type]));
    write(2, "\n", 1);
    return (1);
}

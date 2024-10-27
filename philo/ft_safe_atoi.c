/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_atoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:23:24 by dosokin           #+#    #+#             */
/*   Updated: 2024/10/18 21:06:09 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdbool.h>

static int	error_case(bool *error, t_err type)
{
	*error = true;
	error_manager(type);
	return (0);
}

static size_t	get_size(char *s)
{
	size_t	i;
	size_t	c;

	if (!s)
		return (-1);
	i = 0;
	c = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] == '0')
		i++;
	while (s[i])
	{
		i++;
		c++;
	}
	return (c);
}

static bool	is_syntax_valid(char *s)
{
	size_t	i;

	if (!s)
		return (false);
	i = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		i++;
		if (s[i] < '0' || s[i] > '9')
			return (false);
	}
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	ft_safe_atoi(char *s, bool *error)
{
	unsigned int	result;
	bool			negative;
	size_t			i;

	result = 0;
	if (!is_syntax_valid(s))
		return (error_case(error, SYNTAX_ERR));
	if (get_size(s) > 11)
		return (error_case(error, INT_OVERFLOW));
	negative = s[0] == '-';
	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}
	if ((negative && result > ((unsigned int)INT_MAX + 1)) || (!negative
			&& result > INT_MAX))
		return (error_case(error, INT_OVERFLOW));
	if (negative)
		result *= -1;
	return ((int)result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:23:14 by dosokin           #+#    #+#             */
/*   Updated: 2024/01/28 16:47:52 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <limits.h>

static int	ov(int c, int *flag_error, long r, int x)
{
	if (x == 1)
	{
		if (r > (long)UINT_MAX)
		{
			*flag_error = -1;
			return (-1);
		}
	}
	if (x == 2)
	{
		if (c == 0 || c > 20)
		{
			*flag_error = -1;
			return (-1);
		}
	}
	return (1);
}

static int	ft_atoi_init(int *flag_error, const char *nptr, int *i, int *c)
{
	while (nptr[*i] == 32 || (nptr[*i] >= 9 && nptr[*i] <= 13))
		*i = *i + 1;
	if (nptr[*i] == '+' || nptr[*i] == '-')
	{
		if (nptr[*i] == '-')
		{
			*flag_error = -1;
			return (-1);
		}
		*i = *i + 1;
	}
	while (nptr[*i] == '0')
	{
		*i = *i + 1;
		*c = 1;
	}
	return (1);
}

int	ft_atoui_safe(const char *nptr, int *flag_error)
{
	int			i;
	long long	r;
	int			c;

	r = 0;
	i = 0;
	c = 0;
	if (ft_atoi_init(flag_error, nptr, &i, &c) == -1)
		return (-1);
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		r = r * 10 + (nptr[i] - '0');
		i++;
		c++;
	}
	if (nptr[i] && !(nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13)))
		*flag_error = -1;
	if ((ov(c, flag_error, r, 1) == -1) || ov(c, flag_error, r, 2) == -1)
		return (-1);
	return ((unsigned int)r);
}

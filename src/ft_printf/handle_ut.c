/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:13:56 by vgoldman          #+#    #+#             */
/*   Updated: 2019/12/03 15:30:54 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_isflag(char c)
{
	if (c == '-' || c == '0' || c == '+' || c == ' ' || c == '#' || c == 39)
		return (1);
	else
		return (0);
}

int		ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int		ft_atoi(char **str)
{
	int		sign;
	int		res;

	sign = 1;
	res = 0;
	while (**str == '\t' || **str == '\n' || **str == '\f' || **str == '\r' ||
		**str == ' ' || **str == '\v')
		(*str)++;
	if (**str == '-')
	{
		sign *= -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	while (**str && **str >= '0' && **str <= '9')
	{
		res = (res * 10) + (**str - '0');
		(*str)++;
	}
	return (res * sign);
}

void	ft_putnchar(char c, int n, int *count)
{
	int i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		(*count)++;
		i++;
	}
}

int		ft_abs(int n)
{
	return (n < 0 ? -n : n);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ut2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:02:46 by vgoldman          #+#    #+#             */
/*   Updated: 2019/12/02 14:26:05 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putnstr(char *str, int n, int *count)
{
	int i;

	i = 0;
	while (i < n)
	{
		ft_putnchar(*(str++), 1, count);
		i++;
	}
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (*(str++))
		i++;
	return (i);
}

void	ft_putnbr(long int nb, int *count)
{
	long int a;

	a = nb;
	if (a < 0)
		a = a * (-1);
	if (a > 9)
	{
		ft_putnbr(a / 10, count);
		ft_putnchar(a % 10 + '0', 1, count);
	}
	else
		ft_putnchar(a + '0', 1, count);
}

int		len_nb(long int n)
{
	int i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

void	ft_putnbr_hexa(long int nb, int *count, char *str)
{
	long int a;

	a = nb;
	if (a < 0)
		a = a * (-1);
	if (a > 15)
	{
		ft_putnbr_hexa(a / 16, count, str);
		ft_putnchar(*(a % 16 + str), 1, count);
	}
	else
		ft_putnchar(*(a + str), 1, count);
}

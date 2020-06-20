#include "minishell.h"

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	while (n--)
		*d++ = *s++;
	return (dst);
}

static int	length(int n)
{
	int i;

	i = 0;
	if (n == -2147483648)
		return (12);
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
	return (i);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		nb;

	nb = n;
	i = length(nb) + 1;
	if (!(res = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (nb == -2147483648)
		return (ft_memcpy(res, "-2147483648", i));
	res[i--] = '\0';
	if (nb == 0)
		return (ft_memcpy(res, "0", 2));
	if (nb < 0)
	{
		res[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		res[i--] = '0' + (nb % 10);
		nb /= 10;
	}
	return (res);
}

#include "minishell.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
}

int		ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(res = (char *)malloc(sizeof(char) * (ft_strlen(s1) +
		ft_strlen(s2) + 1))))
		return (NULL);
	while (i < ft_strlen(s1))
	{
		res[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	char	*res;
	int		i;
	int		st;

	str = (char *)s;
	res = NULL;
	i = 0;
	st = start;
	if (!str || len == 0 || ft_strlen(str) + 1 < start)
		return (ft_calloc(sizeof(char), 1));
	while (s[i] && i < len)
		i++;
	if (!(res = (char *)malloc((i + 1) * sizeof(char))))
		return (0);
	i = 0;
	while (*str && len > 0)
	{
		res[i++] = str[st++];
		len--;
	}
	res[i] = '\0';
	return (res);
}

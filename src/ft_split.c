#include "minishell.h"

static int	count_words(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*malloc_word(char *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!(word = (char *)malloc((sizeof(char) * (i + 1)))))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	char	**arr;
	char	*str;

	i = 0;
	str = (char *)s;
	if (!str)
		return (NULL);
	if (!(arr = (char **)malloc(sizeof(char *) * (count_words(str, c) + 1))))
		return (NULL);
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str && *str != c)
		{
			arr[i] = malloc_word(str, c);
			i++;
			while (*str && *str != c)
				str++;
		}
	}
	arr[i] = NULL;
	return (arr);
}

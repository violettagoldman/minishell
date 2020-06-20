#include "minishell.h"

extern t_minishell g_minishell;

char	*new_str(char *str, char *key, int a, int b)
{
	char	*res_tmp;
	char	*res;
	char	*value;

	value = get_env(key);
	res_tmp = ft_strjoin(ft_substr(str, 0, a), value);
	res = ft_strjoin(res_tmp, ft_substr(str, b, ft_strlen(str) - b));
	free(res_tmp);
	return (res);
}

char	*filter_nonexistent(char *str)
{
	char	**split;
	char	*res;
	int		i;
	int		j;

	i = 0;
	split = ft_split(str, ' ');
	res = "";
	while (split[i])
	{
		j = 0;
		while (split[i][j] && split[i][j] != '$')
			j++;
		res = ft_strjoin(res, ft_substr(split[i], 0, j));
		res = ft_strjoin(res, " ");
		//free(split[i]);
		i++;
	}
	return (res);
}

char	*replace(char *str)
{
	int		i;
	int		j;
	char	**split;
	char	*key;

	i = 0;
	while (g_minishell.envp[i])
	{
		split = ft_split(g_minishell.envp[i], '=');
		key = ft_strjoin("$", split[0]);
		j = -1;
		while (str[++j])
		{
			if (!ft_strncmp((str + j), key, ft_strlen(key)))
			{
				str = new_str(str, split[0], j, j + ft_strlen(key));
			}
		}
		i++;
		free(key);
		while (*split)
			free(*(split++));
	}
	return (filter_nonexistent(str));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:58:22 by vgoldman          #+#    #+#             */
/*   Updated: 2020/06/29 14:58:22 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

/*
** Creates a new string that replaces variable key at position a to b with
** value of the environment variable.
** 'echo $A', 'A', 5, 6 --> 'echo 42'
** @param	str	the source string
** @param	key	the environment variable key
** @param	a		start position of the key
** @param	b		end position of the key
** @return		the new string
*/

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

/*
** Once we replace every existent variables, we replace inexistent variables
** with blank.
** @param	str	the source string
** @return 		the source string without '$[A-B]*'
*/

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
		free(split[i]);
		i++;
	}
	return (res);
}

/*
** Takes a string and replace all '$' followed by environment variable key by
** the environment variable value.
** @param	str	the source string
** @return 		the source with environment variables replaced.
*/

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

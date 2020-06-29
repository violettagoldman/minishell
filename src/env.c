/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarx <tmarx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:21:34 by tmarx             #+#    #+#             */
/*   Updated: 2020/06/29 14:12:32 by tmarx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

/*
** Get the full path of a given binary.
** 'ls' gives '/bin/ls'
** '/bin/ls' gives '/bin/ls'
** @param	cmd	the binary name
** @return		the full path of the binary
*/

char	*get_path(char *cmd)
{
	char		**paths;
	struct stat	buffer;
	char		*file_name;

	paths = ft_split(get_env("PATH"), ':');
	if (!stat(cmd, &buffer))
		return (cmd);
	while (*paths)
	{
		if (!(file_name = (char *)ft_calloc(sizeof(char),
			(ft_strlen(cmd) + ft_strlen(*paths) + 2))))
			return (NULL);
		file_name = ft_strcat(file_name, *paths);
		file_name = ft_strcat(file_name, "/");
		file_name = ft_strcat(file_name, cmd);
		if (!stat(file_name, &buffer))
			return (file_name);
		free(file_name);
		paths++;
	}
	return (NULL);
}

/*
** Get the value of the given environment variable.
** 'home' gives '/home/user'
** @param	cmd	the key of the variable
** @return		the value of the variable
*/

char	*get_env(char *var)
{
	char	**env;
	char	**res;
	char	*key;

	env = g_minishell.envp;
	if (!(key = (char *)ft_calloc(sizeof(char), ft_strlen(var) + 2)))
		return (NULL);
	ft_strcat(key, var);
	ft_strcat(key, "=");
	while (*env)
	{
		if (!ft_strncmp(*env, key, ft_strlen(key)))
		{
			res = ft_split(*env, '=');
			free(res[0]);
			free(key);
			return (res[1]);
		}
		env++;
	}
	free(key);
	return (NULL);
}

/*
** Returns the index of a environment variable.
** @param	key	evnironmental variable
** @return		index in the envp list
*/

int		get_env_index(char *var)
{
	int		i;
	char	*key;

	i = 0;
	if (!(key = (char *)ft_calloc(sizeof(char), ft_strlen(var) + 2)))
		return (0);
	ft_strcat(key, var);
	ft_strcat(key, "=");
	while (g_minishell.envp[i])
	{
		if (!ft_strncmp(g_minishell.envp[i], key, ft_strlen(key)))
		{
			free(key);
			return (i);
		}
		++i;
	}
	free(key);
	return (-1);
}

/*
** Adds an environment variable.
** @param	var	equality to be inserted in the envp list
*/

void	add_env(char *var)
{
	char	**envp;
	char	**split;
	int		i;

	i = 0;
	split = ft_split(var, '=');
	remove_env(split[0]);
	while (*split)
		free(*(split++));
	while (g_minishell.envp[i])
		i++;
	if (!(envp = (char **)ft_calloc(sizeof(char *), i + 2)))
		return ;
	i = 0;
	while (g_minishell.envp[i])
	{
		envp[i] = g_minishell.envp[i];
		i++;
	}
	envp[i] = var;
	g_minishell.envp = envp;
}

/*
** Remove a variable from environment variables.
** @param	var	the key of the variable
*/

void	remove_env(char *var)
{
	int		i;
	int		j;
	char	**res;
	int		index;

	i = 0;
	if ((index = get_env_index(var)) == -1)
		return ;
	while (g_minishell.envp[i])
		i++;
	if (!(res = (char **)ft_calloc(sizeof(char *), i + 1)))
		return ;
	i = 0;
	j = 0;
	while (g_minishell.envp[i])
	{
		if (i != index)
			res[j++] = g_minishell.envp[i];
		i++;
	}
	g_minishell.envp = res;
}

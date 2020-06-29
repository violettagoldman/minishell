/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:59:41 by vgoldman          #+#    #+#             */
/*   Updated: 2020/06/29 20:25:56 by vgoldman         ###   ########.fr       */
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
	char				**paths;
	struct stat	buffer;
	char				*file_name[2];
	int					i;

	i = 0;
	file_name[1] = get_env("PATH");
	paths = ft_split(file_name[1], ':');
	if (!stat(cmd, &buffer))
		return (cmd);
	while (paths[i])
	{
		if (!(file_name[0] = (char *)ft_calloc(sizeof(char),
			(ft_strlen(cmd) + ft_strlen(paths[i]) + 2))))
			return (NULL);
		file_name[0] = ft_strcat(file_name[0], paths[i]);
		file_name[0] = ft_strcat(file_name[0], "/");
		file_name[0] = ft_strcat(file_name[0], cmd);
		if (!stat(file_name[0], &buffer))
		{
			free(file_name[1]);
			free_splits(paths);
			return (file_name[0]);
		}
		free(file_name[0]);
		i++;
	}
	free(file_name[1]);
	free_splits(paths);
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
	if (g_minishell.envp_malloc)
		free(g_minishell.envp);
	g_minishell.envp = envp;
	g_minishell.envp_malloc = 1;
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
		else
			free(g_minishell.envp[i]);
		i++;
	}
	g_minishell.envp = res;
}

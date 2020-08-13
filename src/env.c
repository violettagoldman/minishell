/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:59:41 by vgoldman          #+#    #+#             */
/*   Updated: 2020/08/13 13:49:00 by vgoldman         ###   ########.fr       */
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
	char		*file_name[2];
	int			i;

	i = 0;
	if (!ft_strncmp("./", cmd, 2) || !ft_strncmp("/", cmd, 1))
		return (get_relative_path(cmd));
	file_name[1] = get_env("PATH");
	if (!file_name[1])
		return (NULL);
	paths = ft_split(file_name[1], ':');
	while (paths[i])
	{
		create_filename(paths[i], cmd, file_name);
		if (!stat(file_name[0], &buffer))
		{
			free_file_name_and_paths(file_name[1], paths);
			return (file_name[0]);
		}
		free(file_name[0]);
		i++;
	}
	free_file_name_and_paths(file_name[1], paths);
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
	char	*tmp;

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
			tmp = ft_strjoin(res[1], "");
			free_splits(res);
			free(key);
			return (tmp);
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
	free_splits(split);
	while (g_minishell.envp[i])
		i++;
	if (!(envp = (char **)ft_calloc(sizeof(char *), i + 2)))
		return ;
	i = 0;
	while (g_minishell.envp[i])
	{
		envp[i] = ft_strjoin(g_minishell.envp[i], "");
		i++;
	}
	envp[i] = ft_strjoin(var, "");
	free_splits(g_minishell.envp);
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
			res[j++] = ft_strjoin(g_minishell.envp[i], "");
		i++;
	}
	free_splits(g_minishell.envp);
	g_minishell.envp = res;
}

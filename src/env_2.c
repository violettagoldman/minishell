/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarx <tmarx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 13:36:52 by tmarx             #+#    #+#             */
/*   Updated: 2020/07/01 16:57:50 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Takes the envp array given in the main, and copy it. It allows us to free
** its content later.
** @param envp original envp array
** @return the new envp malloced
*/

char	**copy_envp(char **envp)
{
	int		i;
	char	**res;

	i = 0;
	while (envp[i])
		i++;
	if (!(res = (char **)ft_calloc(sizeof(char *), i + 1)))
		return (NULL);
	i = 0;
	while (envp[i])
	{
		res[i] = ft_strjoin(envp[i], "");
		i++;
	}
	res[i] = NULL;
	return (res);
}

/*
** Construct absolute path for a file.
*/

void	create_filename(char *path, char *cmd, char *file_name[2])
{
	if (!(file_name[0] = (char *)ft_calloc(sizeof(char),
		(ft_strlen(cmd) + ft_strlen(path) + 2))))
		return ;
	file_name[0] = ft_strcat(file_name[0], path);
	file_name[0] = ft_strcat(file_name[0], "/");
	file_name[0] = ft_strcat(file_name[0], cmd);
}

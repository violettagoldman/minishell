/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarx <tmarx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 13:36:52 by tmarx             #+#    #+#             */
/*   Updated: 2020/07/01 13:43:16 by tmarx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Takes the envp array given in the main, and copy it. It allows us to free
** its content later.
** @param envp original envp array
** @return the new envp malloced
*/

char  **copy_envp(char **envp)
{
  int   i;
  char  **res;

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

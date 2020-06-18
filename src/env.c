#include "minishell.h"

extern t_minishell g_minishell;

char	*get_path(char *cmd)
{
	char		**paths;
	struct stat	buffer;
	char		*file_name;

	paths = ft_split(get_env("PATH="), ':');
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

char	*get_env(char *key)
{
	char	**env;
	char	**res;

	env = g_minishell.envp;
	while (*env)
	{
		if (!ft_strncmp(*env, key, ft_strlen(key)))
		{
			res = ft_split(*env, '=');
			free(res[0]);
			return (res[1]);
		}
		env++;
	}
	return (NULL);
}

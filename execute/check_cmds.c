/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:32:41 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/05/04 18:09:37 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	path_is_executable(char *cmdpath);
static void	join_withslash(char **res);

int	check_if_valid(t_pipeline *plist)
{
	char	**paths;
	char	*cmd;
	char	*res;
	int		i;

	cmd = ft_strdup(plist->cmd);
	if (cmd[0] == '.' || cmd[0] == '/')
		return (path_is_executable(cmd));
	paths = check_cmd_path(plist->cmd);
	i = -1;
	while (paths[++i])
	{
		res = ft_strjoin(paths[i], cmd);
		if (access(res, X_OK) != -1)
		{
			free(plist->cmd);
			plist->cmd = res;
			return (free(cmd), 1);
		}
	}
	ft_fprintf(2, "bash: %s: command not found\n", cmd);
	return (free(cmd), -1);
}

char	**check_cmd_path(char *cmd)
{
	char	**paths;
	int		i;

	paths = NULL;
	i = -1;
	while (g_glob.envp[++i])
	{
		if (!ft_strncmp(g_glob.envp[i], "PATH=", 5))
		{
			paths = ft_split(g_glob.envp[i] + 5, ':');
			break ;
		}
	}
	if (!paths)
	{
		ft_fprintf(2, "sh: %s: No such file or directory\n", cmd);
		exit(127);
	}
	join_withslash(paths);
	return (paths);
}

static int	path_is_executable(char *cmdpath)
{
	if (access(cmdpath, X_OK) == -1)
	{
		ft_fprintf(2, "sh: %s: No such file or directory\n", cmdpath);
		free(cmdpath);
		return (-1);
	}
	free(cmdpath);
	return (1);
}

static void	join_withslash(char **res)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (res[++i])
		res[i] = ft_strjoin(res[i], "/");
}

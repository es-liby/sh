/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:32:41 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/05/03 21:27:24 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	join_withslash(char **res);

int	check_if_valid(t_pipeline *plist, char **paths)
{
	int		i;
	char	*res;
	char	*cmd;

	cmd = ft_strdup(plist->cmd);
	if (cmd[0] == '.' || cmd[0] == '/')
	{
		if (access(cmd, X_OK) == -1)
		{
			ft_fprintf(2, "bash: %s: No such file or directory\n", plist->cmd);
			return (free(cmd), EOF);
		}
		return (free(cmd), true);
	}
	i = -1;
	while (paths[++i])
	{
		res = ft_strjoin(paths[i], cmd);
		if (access(res, X_OK) != -1)
		{
			free(plist->cmd);
			plist->cmd = res;
			return (free(cmd), true);
		}
	}
	ft_fprintf(2, "bash: %s: command not found\n", cmd);
	return (free(cmd), EOF);
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


int	execute_builtin(t_pipeline **plist)
{
	int	stdin_dup;
	int	stdout_dup;

	if (dup_streams(*plist, &stdin_dup, &stdout_dup) == EOF)
		return (*plist = (*plist)->next, 1);
	if (!ft_strcmp((*plist)->cmd, "pwd"))
		pwdcmd((*plist)->args + 1);
	else if (!ft_strcmp((*plist)->cmd, "export"))
		exportcmd((*plist)->args + 1);
	else if (!ft_strcmp((*plist)->cmd, "echo"))
		echocmd((*plist)->args + 1);
	else if (!ft_strcmp((*plist)->cmd, "cd"))
		cdcmd((*plist)->args + 1);
	else if (!ft_strcmp((*plist)->cmd, "env"))
		envcmd((*plist)->args + 1);
	else if (!ft_strcmp((*plist)->cmd, "exit"))
		exitcmd((*plist)->args + 1);
	else if (!ft_strcmp((*plist)->cmd, "unset"))
		unsetcmd((*plist)->args + 1);
	else
		return (getback_io_streams(*plist, stdin_dup, stdout_dup), 0);
	getback_io_streams(*plist, stdin_dup, stdout_dup);
	*plist = (*plist)->next;
	return (1);
}

bool	check_if_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
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

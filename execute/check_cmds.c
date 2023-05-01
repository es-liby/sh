/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:32:41 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/04/29 17:32:42 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
			ft_fprintf(2, "bash: %s: command not found\n", cmd);
			return (EOF);
		}
		return (true);
	}
	i = -1;
	while (paths[++i])
	{
		res = ft_strjoin(paths[i], cmd);
		if (access(res, X_OK) == 0)
		{
			free(plist->cmd);
			plist->cmd = res;
			return (true);
		}
	}
	ft_fprintf(2, "bash: %s: command not found\n", cmd);
	return (EOF);
}

char	**check_cmd_path(void)
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
		return (NULL);
	join_withslash(paths);
	return (paths);
}


int	check_if_build_in(t_pipeline **plist)
{
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
		return (0);
	*plist = (*plist)->next;
	return (1);
}

void	join_withslash(char **res)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (res[++i])
		res[i] = ft_strjoin(res[i], "/");
}

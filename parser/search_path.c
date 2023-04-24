/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:03:45 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/24 12:06:13 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_a_directory(char *cmd);
int			is_a_path_or_a_directory(char *cmd);

int	search_and_set_path_for_cmds(t_pipeline *plist)
{
	char	*cmd_path;

	if (*(plist->cmd) == '\0')
	{
		ft_fprintf(2, "bash: %s: command not found\n", plist->cmd);
		return (update_exit_status(127), EOF);
	}
	if (is_a_path_or_a_directory(plist->cmd))
		return (true);
	cmd_path = getpath(plist->cmd);
	if (cmd_path == NULL)
		return (EOF);
	free(plist->cmd);
	plist->cmd = cmd_path;
	return (true);
}

int	is_a_path_or_a_directory(char *cmd)
{
	return (*cmd == '.' || *cmd == '/' || is_a_directory(cmd));
}

static int	is_a_directory(char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) == -1)
		return (false);
	if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
		return (true);
	return (false);
}

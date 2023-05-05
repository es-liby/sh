/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:33:01 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/05/05 08:00:47 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	child_process(t_pipeline *plist, t_pipeline *head);
static bool	cmd_is_a_directory(char *cmd);
static bool	check_if_cmd_null(t_pipeline **plist);

void	execute(t_pipeline *plist)
{
	int			id;
	t_pipeline	*head;
	t_ids		*ids;

	ids = NULL;
	if (!plist)
		return ;
	head = plist;
	while (plist)
	{
		if (check_if_cmd_null(&plist) || if_builtin_execute(&plist))
			continue ;
		id = ft_fork();
		if (id < 0)
		{
			plist = plist->next;
			return ;
		}
		if (id == 0)
			child_process(plist, head);
		add_id(&ids, id);
		plist = plist->next;
	}
	close_streams(head);
	wait_pids_and_update_exit_status(&ids);
}

static void	child_process(t_pipeline *plist, t_pipeline *head)
{
	if (plist->in_stream == -1 || plist->out_stream == -1)
		exit(1);
	if (*(plist->cmd) == '\0' || ft_isallblank(plist->cmd))
	{
		ft_fprintf(2, "sh: %s: command not found\n", plist->cmd);
		exit(127);
	}
	split_plist(plist);
	if (check_if_valid(plist) == -1)
		exit(127);
	if (cmd_is_a_directory(plist->cmd))
	{
		ft_fprintf(2, "sh: %s: is a directory\n", plist->cmd);
		exit(126);
	}
	if (duplicate_io_streams(plist) == -1)
		exit(1);
	close_streams(head);
	handle_signals_for_cmds();
	execve(plist->cmd, plist->args, g_glob.envp);
	perror("sh: execve");
	exit(1);
}

static bool	cmd_is_a_directory(char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) == -1)
		exit_with_errmsg(cmd, errno, 1);
	return (S_ISDIR(statbuf.st_mode));
}

void	update_exit_status(int status)
{
	if (WIFEXITED(status))
		g_glob.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_glob.exit_status = WTERMSIG(status) + 128;
}

static bool	check_if_cmd_null(t_pipeline **plist)
{
	if ((*plist)->cmd)
		return (0);
	*plist = (*plist)->next;
	return (1);
}

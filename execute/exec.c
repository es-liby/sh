/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:00:00 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/27 10:20:02 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	if_its_builtin_then_execute(t_pipeline **plist);
static void	executecmd(t_pipeline *plist, t_pipeline **head);
static bool	cmd_is_a_directory(char *cmd);

int	execute(t_pipeline *plist)
{
	t_pipeline	*head;
	pid_t		pid;
	t_ids		*ids;

	if (plist == NULL || plist->cmd == NULL)
		return (true);
	ids = NULL;
	head = plist;
	while (plist)
	{
		if (if_its_builtin_then_execute(&plist) == true)
			continue ;
		pid = fork();
		if (pid == -1)
			return (perror("fork"), EOF);
		if (pid == 0)
			executecmd(plist, &head);
		add_id(&ids, pid);
		plist = plist->next;
	}
	close_streams(head);
	wait_pids_and_update_exit_status(&ids);
	return (true);
}

static void	executecmd(t_pipeline *plist, t_pipeline **head)
{
	char		*cmd;
	char		**args;
	void		handle_signals_for_cmds(void);

	if (duplicate_io_streams(plist) == EOF)
		exit(EXIT_FAILURE);
	if (close_streams(*head) == EOF)
		exit(EXIT_FAILURE);
	split_plist(plist);
	if (search_and_set_path_for_cmds(plist) == EOF)
		exit(127);
	cmd = plist->cmd;
	args = plist->args;
	if (cmd_is_a_directory(cmd))
	{
		ft_fprintf(2, "sh: %s: Is a directory\n", cmd);
		exit(126);
	}
	handle_signals_for_cmds();
	execve(cmd, args, g_glob.envp);
	perror("execve");
	exit(1);
}

static int	if_its_builtin_then_execute(t_pipeline **plist)
{
	t_builtin	cmdtype;

	cmdtype = is_a_builtin_cmd((*plist)->cmd);
	if (cmdtype == NONE)
		return (false);
	execute_builtin_cmd(*plist, cmdtype);
	*plist = (*plist)->next;
	return (true);
}

static bool	cmd_is_a_directory(char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) == -1)
		exit_with_errmsg(cmd, errno, 1);
	if (S_ISDIR(statbuf.st_mode))
		return (true);
	return (false);
}

void	update_exit_status(int status)
{
	if (WIFEXITED(status))
		g_glob.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_glob.exit_status = WTERMSIG(status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execcc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:33:01 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/05/01 15:10:42 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	child_process(t_pipeline *plist, t_pipeline *head, char **paths);
static bool	cmd_is_a_directory(char *cmd);

void	executee(t_pipeline *plist)
{
	int			id;
	char		**paths;
	t_pipeline	*head;
	t_ids		*ids;

	paths = check_cmd_path();
	ids = NULL;
	if (!plist || plist->cmd == NULL)
		return ;
	head = plist;
	while (plist)
	{
		if (check_if_build_in(&plist))
			continue ;
		id = ft_fork();
		if (id < 0)
		{
			plist = plist->next;
			continue ;			
		}
		if (id == 0)
			child_process(plist, head, paths);
		add_id(&ids, id);
		plist = plist->next;
	}
	free_tab(paths);
	close_streams(head);
	wait_pids_and_update_exit_status(&ids);
}

static void	child_process(t_pipeline *plist, t_pipeline *head, char **paths)
{
	char	**h;

	h = ft_split(plist->cmd, ' ');
	if (h[1])
	{
		free(plist->cmd);
		plist->cmd = ft_strdup(h[0]);
		free_tab(plist->args);
		plist->args = h;
	}
	if (check_if_valid(plist, paths) == EOF)
		exit(127);
	if (cmd_is_a_directory(plist->cmd))
	{
		ft_fprintf(2, "sh: %s: is a directory\n", plist->cmd);
		exit(126);
	}
	if (plist->in_stream != 0 && dup2(plist->in_stream, 0) < 0)
		exit(EXIT_FAILURE);
	if (plist->out_stream != 1 && dup2(plist->out_stream, 1) < 0)
		exit(EXIT_FAILURE);
	close_streams(head);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(plist->cmd, plist->args, g_glob.envp);
	perror("sh");
	exit(1);
}

static bool	cmd_is_a_directory(char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) == -1)
		exit_with_errmsg(cmd, errno, 1);
	return (S_ISDIR(statbuf.st_mode));
}

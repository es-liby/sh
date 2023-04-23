/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:43:01 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/23 09:03:46 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_global	g_gbl;

void	f(void)
{
	system("leaks minishell");
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	//atexit(f);
	if (argc != 1)
	{
		ft_fprintf(2, "Usage: ./minishell\n");
		exit(EXIT_FAILURE);
	}
	g_gbl.envlist = envcpy(envp);
	g_gbl.exit_status = 0;
	g_gbl.fds = NULL;
	g_gbl.heredoc_file = NULL;
	if (isatty(0) == 0)
		exit(EXIT_FAILURE);
	prompt(envp);
	unlink_heredoc_file();
	clearenv(g_gbl.envlist);
	// ft_lstclear(&g_gbl.envlist, free);
	exit(EXIT_SUCCESS);
}

void	prompt(char *envp[])
{
	t_list		*tokens;
	t_pipeline	*plist;
	char		*pipeline;
	int			stdin_dup;

	(void)envp;
	stdin_dup = dup(STDIN_FILENO);
	while (true)
	{
		g_gbl.envp = get_envp();
		handle_signals();
		if (isatty(STDIN_FILENO) == 0)
			dup2(stdin_dup, STDIN_FILENO);
		pipeline = readline("\x1B[33msh$>\x1B[0m ");
		if (pipeline == NULL)
		{
			if (isatty(STDIN_FILENO) == 0)
				continue ;
			break ;
		}
		if (*pipeline)
			add_history(pipeline);
		if (scanner(&tokens, pipeline) == NIL)
		{
			free(pipeline);
			continue ;
		}
		free(pipeline);
		if (parser(&tokens, &plist) != EOF)
			execute(plist);
		free_tab(g_gbl.envp);
		// printplist(plist);
		unlink_heredoc_file();
		clear_plist(&plist);
		ft_lstclear(&tokens, free);
	}
	close(stdin_dup);
}

void	unlink_heredoc_file(void)
{
	if (g_gbl.heredoc_file == NULL)
		return ;
	if (unlink(g_gbl.heredoc_file) == -1)
	{
		perror("unlink");
		return ;
	}
	free(g_gbl.heredoc_file);
	g_gbl.heredoc_file = NULL;
}

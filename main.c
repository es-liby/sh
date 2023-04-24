/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:43:01 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/24 11:59:45 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_global	g_gbl;

static int	scan_and_parse(char *pipeline, t_list **tokens, t_pipeline **plist);
static void	cleanup(t_pipeline **plist, t_list **tokens);

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
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
	prompt();
	unlink_heredoc_file();
	clearenv(g_gbl.envlist);
	exit(EXIT_SUCCESS);
}

void	prompt(void)
{
	t_list		*tokens;
	t_pipeline	*plist;
	char		*pipeline;
	int			stdin_dup;

	stdin_dup = dup(STDIN_FILENO);
	while (true)
	{
		handle_signals();
		if (isatty(STDIN_FILENO) == 0)
			dup2(stdin_dup, STDIN_FILENO);
		pipeline = readline("\x1B[33msh$>\x1B[0m ");
		if (pipeline == NULL)
			break ;
		if (*pipeline)
			add_history(pipeline);
		if (scan_and_parse(pipeline, &tokens, &plist) == EOF)
			continue ;
		execute(plist);
		cleanup(&plist, &tokens);
	}
	close(stdin_dup);
}

static int	scan_and_parse(char *pipeline, t_list **tokens, t_pipeline **plist)
{
	if (scanner(tokens, pipeline) == NIL)
		return (free(pipeline), EOF);
	free(pipeline);
	g_gbl.envp = get_envp();
	g_gbl.sigint = OFF;
	if (parser(tokens, plist) == EOF)
		return (cleanup(plist, tokens), EOF);
	return (true);
}

static void	cleanup(t_pipeline **plist, t_list **tokens)
{
	unlink_heredoc_file();
	close_pipes();
	free_tab(g_gbl.envp);
	clear_plist(plist);
	ft_lstclear(tokens, free);
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
	printf("heredoc file: %s\n", g_gbl.heredoc_file);
	free(g_gbl.heredoc_file);
	g_gbl.heredoc_file = NULL;
}

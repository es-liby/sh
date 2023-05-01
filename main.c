/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:43:01 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/01 12:47:19 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_global	g_glob;

static int	scan_and_parse(char *pipeline, t_list **tokens, t_pipeline **plist);

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	if (argc != 1)
		exit_usage_err();
	g_glob.envlist = envcpy(envp);
	update_shell_level();
	g_glob.exit_status = 0;
	g_glob.fds = NULL;
	g_glob.heredoc_file = NULL;
	if (isatty(0) == 0)
		exit(EXIT_FAILURE);
	prompt();
	unlink_heredoc_file();
	clearenv(g_glob.envlist);
	exit(EXIT_SUCCESS);
}

void	prompt(void)
{
	t_list		*tokens;
	t_pipeline	*plist;
	char		*pipeline;
	int			stdin_dup;

	stdin_dup = dup(STDIN_FILENO);
	if (stdin_dup == -1)
		return ;
	while (true)
	{
		handle_signals();
		if (isatty(STDIN_FILENO) == 0)
			if (ft_dup2(stdin_dup, STDIN_FILENO) == EOF)
				break ;
		pipeline = readline("\x1B[33msh$>\x1B[0m ");
		if (pipeline == NULL)
			break ;
		if (*pipeline && !ft_isallspace(pipeline))
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
	g_glob.envp = get_envp();
	g_glob.sigint = OFF;
	if (parser(tokens, plist) == EOF)
		return (cleanup(plist, tokens), EOF);
	return (true);
}

void	cleanup(t_pipeline **plist, t_list **tokens)
{
	unlink_heredoc_file();
	close_pipes();
	free_tab(g_glob.envp);
	clear_plist(plist);
	ft_lstclear(tokens, free);
	g_glob.sigint = OFF;
}

void	unlink_heredoc_file(void)
{
	if (g_glob.heredoc_file == NULL)
		return ;
	if (unlink(g_glob.heredoc_file) == -1)
	{
		free(g_glob.heredoc_file);
		perror("unlink");
		return ;
	}
	free(g_glob.heredoc_file);
	g_glob.heredoc_file = NULL;
}

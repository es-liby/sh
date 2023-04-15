/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:52:07 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/15 17:07:15 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_global	g_gbl;

void	printplist(t_pipeline *plist)
{
	while (plist)
	{
		printf("cmd: %s\nargs: %s\nin_stream: %d\nout_stream: %d\n\n", plist->cmd,
			plist->args, plist->in_stream, plist->out_stream);
		plist = plist->next;
	}
}

void	printlist(t_list *tokens)
{
	char		*symbols[] = {
		"REDIR",
		"PIPE",
		"WORD",
		"ENVVAR",
		"DQUOTE",
		"SQUOTE"
	};

	while (tokens)
	{
		printf("Lexeme: %s\n", (char *)(tokens->content));
		printf("\tType: %s\n", symbols[tokens->type]);
		tokens = tokens->next;
	}
}

void	testprint(t_list *tokens)
{
	while (tokens)
	{
		printf("%s\n", (char *)(tokens->content));
		tokens = tokens->next;
	}
}

void	f(void)
{
	system("leaks minishell");
}

void	printenvvar(void)
{
	t_list	*lst_ptr;

	lst_ptr = g_gbl.envlist;
	while (lst_ptr)
	{
		printf("%s\n", (char *)(lst_ptr->content));
		lst_ptr = lst_ptr->next;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int fd = open ("/dev/urandom", O_RDONLY);
	dup2(fd, 0);
	(void)argv;
	//atexit(f);
	if (argc != 1)
	{
		ft_fprintf(2, "Usage: ./minishell\n");
		exit(EXIT_FAILURE);
	}
	g_gbl.envlist = envcpy(envp);
	g_gbl.exit_status = 0;
	g_gbl.heredoc_file = NULL;
	prompt();
	ft_lstclear(&g_gbl.envlist, free);
	exit(EXIT_SUCCESS);
}

void	prompt(void)
{
	t_list		*tokens;
	t_pipeline	*plist;
	char		*pipeline;

	while (true)
	{
		pipeline = readline("\x1B[33msh$>\x1B[0m ");
		if (pipeline == NULL)
			break ;
		if (scanner(&tokens, pipeline) == NIL)
		{
			free(pipeline);
			continue ;
		}
		free(pipeline);
		//printlist(tokens);
		parser(&tokens, &plist);
		//printlist(tokens);
		//printplist(plist);
		unlink_and_close_heredoc_file(plist);
		clear_plist(&plist);
		//testprint(tokens);
		ft_lstclear(&tokens, free);
	}
}

void	unlink_and_close_heredoc_file(t_pipeline *plist)
{
	if (g_gbl.heredoc_file == NULL)
		return ;
	if (unlink(g_gbl.heredoc_file) == -1)
		exit(EXIT_FAILURE);
	while (plist && plist->in_stream < 3)
		plist = plist->next;
	while (plist)
	{
		ft_close(plist->in_stream);
		plist = plist->next;
	}
	free(g_gbl.heredoc_file);
	g_gbl.heredoc_file = NULL;
}

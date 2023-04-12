/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:52:07 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/12 02:10:34 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_global	e_gbl;

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

void	printplist(t_pipeline *plist)
{
	while (plist)
	{
		printf("cmd: %s\n", plist->cmd);
		printf("args: %s\n", plist->args);
		printf("in_stream: %d\n", plist->in_stream);
		printf("out_stream: %d\n", plist->out_stream);
		plist = plist->next;
	}
}

void	printenvvar(void)
{
	t_list	*lst_ptr;

	lst_ptr = e_gbl.envlist;
	while (lst_ptr)
	{
		printf("%s\n", (char *)(lst_ptr->content));
		lst_ptr = lst_ptr->next;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	atexit(f);
	if (argc != 1)
	{
		ft_fprintf(2, "Usage: ./minishell\n");
		exit(EXIT_FAILURE);
	}
	e_gbl.envlist = envcpy(envp);
	e_gbl.exit_status = 0;
	prompt();
	ft_lstclear(&e_gbl.envlist, free);
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
		scanner(&tokens, pipeline);
		free(pipeline);
		//printlist(tokens);
		parser(&tokens, &plist);
		//testprint(tokens);
		ft_lstclear(&tokens, free);
	}
}

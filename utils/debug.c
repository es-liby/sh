/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:16:11 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 18:17:21 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	char		*symbols[4];

	symbols[0] = "REIDIR";
	symbols[1] = "PIPE";
	symbols[2] = "WORD";
	symbols[3] = "ENVVAR";
	while (tokens)
	{
		printf("Lexeme: %s\n", (char *)(tokens->lexeme));
		printf("\tType: %s\n", symbols[tokens->type]);
		tokens = tokens->next;
	}
}

void	testprint(t_list *tokens)
{
	while (tokens)
	{
		printf("%s\n", (char *)(tokens->lexeme));
		tokens = tokens->next;
	}
}

void	printenvvar(void)
{
	t_list	*lst_ptr;

	lst_ptr = g_gbl.envlist;
	while (lst_ptr)
	{
		printf("%s\n", (char *)(lst_ptr->lexeme));
		lst_ptr = lst_ptr->next;
	}
}

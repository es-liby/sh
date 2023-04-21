/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:16:11 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/18 12:19:26 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	printplist(t_pipeline *plist)
{
	while (plist)
	{
		printf("cmd: %s\n", plist->cmd);
		printf("args: ");
		print_args(plist->args);
		printf("in_stream: %d\nout_stream: %d\n", plist->in_stream, plist->out_stream);
		plist = plist->next;
	}
}

void	print_args(char **args)
{
	int	i;

	if (args == NULL)
	{
		printf("(null)\n");
		return ;
	}
	i = 0;
	while (args[i])
	{
		printf("%s ", args[i]);
		i++;
	}
	printf("\n");
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
	t_env	*env_ptr;

	env_ptr = g_gbl.envlist;
	while (env_ptr)
	{
		printf("%s=%s\n", env_ptr->key, env_ptr->value);
		env_ptr = env_ptr->next;
	}
}

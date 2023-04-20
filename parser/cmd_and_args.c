/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:14:53 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/18 12:05:52 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	set_args(t_pipeline **plist, t_list **tokens);
static void	args_after_cmd(t_pipeline **plist, t_list **tokens);
static int	search_and_set_args(t_pipeline **plist, t_list *tokens);
static void	set_pipe(t_pipeline **plist);

int	set_cmd_and_args(t_pipeline **plist, t_list **tokens)
{
	printf("set_cmd_and_args()	-->	(*plist)->cmd\n");
	if ((*plist)->cmd == NULL)
	{
		(*plist)->cmd = ft_strdup((char *)(*tokens)->lexeme);
		advance(tokens);
	}
	printf("set_cmd_and_args()	-->	set_args()\n");
	if (set_args(plist, tokens) == EOF)
		return (EOF);
	printf("set_cmd_and_args()	-->	set_pipes()\n");
	if (g_gbl.fds != NULL)
		set_pipe(plist);
	printf("set_cmd_and_args()	-->	return (true)\n");
	return (true);
}

static int	set_args(t_pipeline **plist, t_list **tokens)
{
	if (peek_type(*tokens) == WORD)
		args_after_cmd(plist, tokens);
	else if (search_and_set_args(plist, *tokens) == EOF)
		return (EOF);
	return (true);
}

static void	args_after_cmd(t_pipeline **plist, t_list **tokens)
{
	char	*args;

	args = ft_strdup((*plist)->cmd);
	args = ft_strjoin(args, " ");
	while (peek_type(*tokens) == WORD)
	{
		args = ft_strjoin(args, (char *)(*tokens)->lexeme);
		args = ft_strjoin(args, " ");
		advance(tokens);
	}
	if (args != NULL)
		(*plist)->args = split_args(args);
}

static int	search_and_set_args(t_pipeline **plist, t_list *tokens)
{
	char	*args;

	args = ft_strdup((*plist)->cmd);
	args = ft_strjoin(args, " ");
	while (peek_type(tokens) != NIL && peek_type(tokens) != PIPE)
	{
		if (is_redir_token(tokens))
		{
			advance(&tokens);
			if (p_match(&tokens, WORD) == false)
				return (syn_err(tokens), EOF);
			continue ;
		}
		args = ft_strjoin(args, (char *)tokens->lexeme);
		args = ft_strjoin(args, " ");
		advance(&tokens);
	}
	if (args != NULL)
		(*plist)->args = split_args(args);
	return (true);
}

static void	set_pipe(t_pipeline **plist)
{
	t_fds	*fds;
	int		i;

	fds = g_gbl.fds;
	i = fds->pipe_counter;
	if (i == 0)
		(*plist)->out_stream = fds->fds[i][1];
	else if (i > 0 && i < fds->n)
	{
		(*plist)->in_stream = fds->fds[i - 1][0];
		(*plist)->out_stream = fds->fds[i][1];
	}
	if (i == fds->n)
		(*plist)->in_stream = fds->fds[i - 1][0];
}

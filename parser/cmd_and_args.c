/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:01:53 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/25 11:49:12 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	set_args(t_pipeline **plist, t_list **tokens);
static void	args_after_cmd(t_pipeline **plist, t_list **tokens);
static int	search_and_set_args(t_pipeline **plist, t_list *tokens);
static void	set_pipe(t_pipeline **plist);

int	set_cmd_and_args(t_pipeline **plist, t_list **tokens)
{
	if ((*plist)->cmd == NULL)
	{
		(*plist)->cmd = ft_strdup((char *)(*tokens)->lexeme);
		advance(tokens);
	}
	if (set_args(plist, tokens) == EOF)
		return (EOF);
	if (g_gbl.fds != NULL)
		set_pipe(plist);
	if (is_redir_token(*tokens))
		return (set_input_and_output_streams(plist, tokens));
	return (true);
}

static int	set_args(t_pipeline **plist, t_list **tokens)
{
	t_list	*arglist;

	arglist = NULL;
	if (peek_type(*tokens) == NIL)
	{
		ft_lstadd_back(&arglist, ft_lstnew(ft_strdup((*plist)->cmd), WORD));
		(*plist)->args = split_argslist(arglist);
		ft_lstclear(&arglist, free);
		return (true);
	}
	else if (peek_type(*tokens) == WORD)
		args_after_cmd(plist, tokens);
	else if (search_and_set_args(plist, *tokens) == EOF)
		return (EOF);
	return (true);
}

static void	args_after_cmd(t_pipeline **plist, t_list **tokens)
{
	t_list	*argslist;
	t_list	*new_token;

	argslist = NULL;
	ft_lstadd_back(&argslist, ft_lstnew(ft_strdup((*plist)->cmd), WORD));
	while (peek_type(*tokens) == WORD)
	{
		new_token = ft_lstnew(ft_strdup((*tokens)->lexeme), WORD);
		ft_lstadd_back(&argslist, new_token);
		advance(tokens);
	}
	if (argslist != NULL)
		(*plist)->args = split_argslist(argslist);
	ft_lstclear(&argslist, free);
}

static int	search_and_set_args(t_pipeline **plist, t_list *tokens)
{
	t_list	*argslist;

	argslist = NULL;
	ft_lstadd_back(&argslist, ft_lstnew(ft_strdup((*plist)->cmd), WORD));
	while (peek_type(tokens) != NIL && peek_type(tokens) != PIPE)
	{
		if (is_redir_token(tokens))
		{
			advance(&tokens);
			if (p_match(&tokens, WORD) == false)
				return (syn_err(tokens), EOF);
			continue ;
		}
		ft_lstadd_back(&argslist, ft_lstnew(ft_strdup((*plist)->cmd), WORD));
		advance(&tokens);
	}
	if (argslist != NULL)
		(*plist)->args = split_argslist(argslist);
	ft_lstclear(&argslist, free);
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

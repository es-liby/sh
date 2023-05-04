/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:01:53 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 08:35:44 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	set_args(t_pipeline **plist, t_list **tokens);
//static void	addarg(t_list **arglist, char *lexeme);
static int	search_and_set_args(t_pipeline **plist, t_list **tokens);

int	set_cmd_and_args(t_pipeline **plist, t_list **tokens)
{
	if ((*plist)->cmd == NULL)
	{
		(*plist)->cmd = ft_strdup((char *)(*tokens)->lexeme);
		advance(tokens);
	}
	if (set_args(plist, tokens) == EOF)
		return (EOF);
	//if (is_redir_token(*tokens))
	//	return (set_input_and_output_streams(plist, tokens));
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
	else if (search_and_set_args(plist, tokens) == EOF)
		return (EOF);
	return (true);
}

static int	search_and_set_args(t_pipeline **plist, t_list **tokens)
{
	t_list	*arglist;
	char	*lexeme_dup;

	arglist = NULL;
	ft_lstadd_back(&arglist, ft_lstnew(ft_strdup((*plist)->cmd), WORD));
	while (peek_type(*tokens) != NIL && peek_type(*tokens) != PIPE)
	{
		if (is_redir_token(*tokens))
		{
			if (set_input_and_output_streams(plist, tokens) == EOF)
				return (ft_lstclear(&arglist, free), EOF);
			continue ;
		}
		lexeme_dup = ft_strdup((*tokens)->lexeme);
		ft_lstadd_back(&arglist, ft_lstnew(lexeme_dup, WORD));
		advance(tokens);
	}
	if (arglist != NULL)
		(*plist)->args = split_argslist(arglist);
	ft_lstclear(&arglist, free);
	return (true);
}

//static void	addarg(t_list **arglist, char *lexeme)
//{
//	t_list	*new;
//	char	*lexeme_dup;

//	lexeme_dup = ft_strdup(lexeme);
//	new = ft_lstnew(lexeme, WORD);
//	ft_lstadd_back(arglist, new);
//}

void	set_pipe(t_pipeline **plist)
{
	t_fds	*fds;
	int		i;

	if (g_glob.fds == NULL)
		return ;
	fds = g_glob.fds;
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

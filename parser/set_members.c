/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_members.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:15:53 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 18:06:13 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int			set_iostreams_and_cmds(t_pipeline **plist, t_list **tokens);
static int			there_is_pipe_token(t_list *tokens);
static bool			go_to_next_cmd(t_list **tokens);
static int			is_not_valid_pipeline(t_list *tokens);

int	perform_redirections_and_set_cmds(t_pipeline **plist, t_list **tokens)
{
	t_pipeline	*new;

	if (there_is_pipe_token(*tokens))
		g_gbl.fds = count_and_open_pipes(*tokens);
	while (*tokens)
	{
		new = new_plist();
		if (set_iostreams_and_cmds(&new, tokens) == EOF)
			return (close_pipes(), clear_plist(&new), EOF);
		addback(plist, new);
		if (g_gbl.fds)
			g_gbl.fds->pipe_counter++;
	}
	return (true);
}

static int	set_iostreams_and_cmds(t_pipeline **plist, t_list **tokens)
{
	if (is_not_valid_pipeline(*tokens))
		return (syn_err(*tokens), EOF);
	if (peek_type(*tokens) == WORD)
		if (set_cmd_and_args(plist, tokens) == EOF)
			return (EOF);
	if (is_redir_token(*tokens))
		if (set_input_and_output_streams(plist, tokens) == EOF)
			return (EOF);
	if (go_to_next_cmd(tokens) == false)
		return (EOF);
	return (true);
}

static int	is_not_valid_pipeline(t_list *tokens)
{
	t_tokentype	type;

	type = peek_type(tokens);
	return (type != WORD && !is_redir_token(tokens));
}

static int	there_is_pipe_token(t_list *tokens)
{
	while (tokens && peek_type(tokens) != PIPE)
		advance(&tokens);
	if (peek_type(tokens) == PIPE)
		return (true);
	return (false);
}

static bool	go_to_next_cmd(t_list **tokens)
{
	while (*tokens && peek_type(*tokens) != PIPE)
		advance(tokens);
	if (peek_type(*tokens) == PIPE)
	{
		if (pipeline_not_completed((*tokens)->next))
			return (complete_pipeline(&(*tokens)->prev));
		advance(tokens);
	}
	return (true);
}

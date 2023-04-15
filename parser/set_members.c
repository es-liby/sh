/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_members.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:15:53 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/15 18:22:49 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int			set_iostreams_and_cmds(t_pipeline **plist, t_list **tokens,
		t_fds *fds);
static int			there_is_pipe_token(t_list *tokens);
static bool			go_to_next_cmd(t_list **tokens);
static int			is_not_valid_pipeline(t_list *tokens);

int	perform_redirections_and_set_cmds(t_pipeline **plist, t_list **tokens)
{
	t_fds		*fds;
	t_pipeline	*new;

	fds = NULL;
	if (there_is_pipe_token(*tokens))
		fds = count_and_open_pipes(*tokens);
	while (*tokens)
	{
		new = new_plist();
		if (set_iostreams_and_cmds(&new, tokens, fds) == EOF)
			return (close_pipes(fds), clear_plist(&new), EOF);
		addback(plist, new);
		fds->pipe_counter++;
	}
	close_pipes(fds);
	return (true);
}

static int	set_iostreams_and_cmds(t_pipeline **plist, t_list **tokens,
	t_fds *fds)
{
	if (is_not_valid_pipeline(*tokens))
		return (print_syntax_error(*tokens), EOF);
	if (peek_type(*tokens) == WORD)
		if (set_cmd_and_args(plist, tokens, fds) == EOF)
			return (EOF);
	if (is_redir_token(*tokens))
		if (set_input_and_output_streams(plist, tokens, fds) == EOF)
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
			return (complete_pipeline(tokens));
		advance(tokens);
	}
	return (true);
}

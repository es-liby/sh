/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_streams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:35:29 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/15 18:16:51 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	set_input_stream(t_pipeline **plist, t_list **tokens, t_fds *fds);
static int	set_output_stream(t_pipeline **plist, t_list **tokens, t_fds *fds);
static int	set_heredoc_for_input(t_pipeline **plist, t_list **tokens,
	t_fds *fds);

int	set_input_and_output_streams(t_pipeline **plist, t_list **tokens, 
	t_fds *fds)
{
	if (p_match(tokens, REDIR_IN))
		if (set_input_stream(plist, tokens, fds) == EOF)
			return (EOF);
	if (p_match(tokens, REDIR_OUT) || p_match(tokens, REDIR_OUT_APPEND))
		if (set_output_stream(plist, tokens, fds) == EOF)
			return (EOF);
	if (p_match(tokens, HEREDOC))
	{
		if (set_heredoc_for_input(plist, tokens, fds) == EOF)
			return (EOF);
	}
	return (true);
}

static int	set_input_stream(t_pipeline **plist, t_list **tokens, t_fds *fds)
{
	if (perform_redir_input(plist, tokens, fds) == EOF)
		return (EOF);
	if (peek_type(*tokens) == WORD)
		return (set_cmd_and_args(plist, tokens, fds));
	return (true);
}

static int	set_output_stream(t_pipeline **plist, t_list **tokens, t_fds *fds)
{
	if (perform_redir_output(plist, tokens, fds) == EOF)
		return (EOF);
	if (peek_type(*tokens) == WORD)
		return (set_cmd_and_args(plist, tokens, fds));
	return (true);
}

static int	set_heredoc_for_input(t_pipeline **plist, t_list **tokens, 
	t_fds *fds)
{
	if (redir_heredoc(plist, tokens, fds) == EOF)
		return (EOF);
	if (peek_type(*tokens) == WORD)
		return (set_cmd_and_args(plist, tokens, fds));
	return (true);
}

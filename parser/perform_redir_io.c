/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_redir_io.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:39:36 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:39:37 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_fd_of_output_file(char *outfile, t_list *token);

int	set_input_and_output_streams(t_pipeline **plist, t_list **tokens)
{
	if (p_match(tokens, REDIR_IN))
		if (perform_redir_input(plist, tokens) == EOF)
			return (EOF);
	if (p_match(tokens, REDIR_OUT) || p_match(tokens, REDIR_OUT_APPEND))
		if (perform_redir_output(plist, tokens) == EOF)
			return (EOF);
	if (p_match(tokens, HEREDOC))
		if (readlines_from_heredoc_prompt(plist, tokens) == EOF)
			return (EOF);
	return (true);
}

int	perform_redir_input(t_pipeline **plist, t_list **tokens)
{
	char	*infile;
	int		fd;

	if (peek_type(*tokens) != WORD)
		return (syn_err(*tokens), EOF);
	infile = (char *)(*tokens)->lexeme;
	fd = ft_open(infile, O_RDONLY);
	(*plist)->in_stream = fd;
	advance(tokens);
	if (is_redir_token(*tokens))
		return (set_input_and_output_streams(plist, tokens));
	return (true);
}

int	perform_redir_output(t_pipeline **plist, t_list **tokens)
{
	char	*outfile;
	int		fd;

	if (peek_type(*tokens) != WORD)
		return (syn_err(*tokens), EOF);
	outfile = (char *)(*tokens)->lexeme;
	fd = get_fd_of_output_file(outfile, *tokens);
	if ((*plist)->out_stream != 1)
		ft_close((*plist)->out_stream);
	(*plist)->out_stream = fd;
	advance(tokens);
	if (is_redir_token(*tokens))
		return (set_input_and_output_streams(plist, tokens));
	return (true);
}

int	is_redir_token(t_list *token)
{
	t_tokentype	type;

	type = peek_type(token);
	return (type == REDIR_IN || type == REDIR_OUT || type == REDIR_OUT_APPEND
		|| type == HEREDOC);
}

static int	get_fd_of_output_file(char *outfile, t_list *token)
{
	int	fd;

	if (peek_previous_type(token) == REDIR_OUT)
		fd = ft_open(outfile, O_WRONLY | O_TRUNC | O_CREAT);
	else
		fd = ft_open(outfile, O_WRONLY | O_APPEND | O_CREAT);
	return (fd);
}

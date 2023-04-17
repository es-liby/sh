/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_redir_io.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 23:02:22 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 11:25:30 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_fd_of_output_file(char *outfile, t_list *token);

int	perform_redir_input(t_pipeline **plist, t_list **tokens, t_fds *fds)
{
	char	*infile;
	int		fd;

	if (peek_type(*tokens) != WORD)
		return (syn_err(*tokens), EOF);
	infile = (char *)(*tokens)->content;
	fd = ft_open(infile, O_RDONLY);
	if (fd == EOF)
		return (EOF);
	(*plist)->in_stream = fd;
	advance(tokens);
	if (is_redir_token(*tokens))
		return (set_input_and_output_streams(plist, tokens, fds));
	return (true);
}

int	perform_redir_output(t_pipeline **plist, t_list **tokens, t_fds *fds)
{
	char	*outfile;
	int		fd;

	if (peek_type(*tokens) != WORD)
		return (syn_err(*tokens), EOF);
	outfile = (char *)(*tokens)->content;
	fd = get_fd_of_output_file(outfile, *tokens);
	if (fd == EOF)
		return (EOF);
	(*plist)->out_stream = fd;
	advance(tokens);
	if (is_redir_token(*tokens))
		return (set_input_and_output_streams(plist, tokens, fds));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 23:02:22 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/12 01:31:25 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_input_stream(t_pipeline **plist, t_list **tokens, t_fds *fds, int i)
{
	char	*infile;
	int		fd;

	if (peek_type(*tokens) != WORD)
		return (print_syntax_error(*tokens), EOF);
	infile = (char *)(*tokens)->content;
	fd = ft_open(infile, O_RDONLY);
	if (fd == EOF)
		return (EOF);
	(*plist)->in_stream = fd;
	advance(tokens);
	if (is_redir_token(*tokens))
		return (set_input_and_output_streams(plist, tokens, fds, i));
	return (true);
}

int	set_output_stream(t_pipeline **plist, t_list **tokens, t_fds *fds, int i)
{
	char	*outfile;
	int		fd;

	if (peek_type(*tokens) != WORD)
		return (print_syntax_error(*tokens), EOF);
	outfile = (char *)(*tokens)->content;
	if (peek_previous_type(*tokens) == REDIR_OUT)
		fd = ft_open(outfile, O_WRONLY | O_TRUNC | O_CREAT);
	else
		fd = ft_open(outfile, O_WRONLY | O_APPEND | O_CREAT);
	if (fd == EOF)
		return (EOF);
	(*plist)->out_stream = fd;
	advance(tokens);
	if (is_redir_token(*tokens))
		return (set_input_and_output_streams(plist, tokens, fds, i));
	return (true);
}

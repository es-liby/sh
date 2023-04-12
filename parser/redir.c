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

static int	getfd_of_file(char *outfile, t_tokentype type);

int	perform_redir_input(t_list **tokens)
{
	char	*outfile;
	int		fd;
	
	if (peek_type(*tokens) != WORD)
		return (print_syntax_error(*tokens), EOF);
	outfile = (char *)(*tokens)->content;
	fd = ft_open(outfile, O_RDONLY);
	if (fd == -1)
		return (EOF);
	if (ft_dup2(fd, 0) == -1)
		return (EOF);
	close(fd);
	advance(tokens);
	return (true);
}

int	perform_redir_output(t_list **tokens, t_tokentype type)
{
	char	*outfile;
	int		fd;

	if (peek_type(*tokens) != WORD)
		return (print_syntax_error(*tokens), EOF);
	outfile = (char *)(*tokens)->content;
	printf("here\n");
	fd = getfd_of_file(outfile, type);
	printf("here\n");
	if (fd == -1)
		return (EOF);
	printf("here\n");
	if (ft_dup2(fd, 1) == -1)
		return (EOF);
	close(fd);
	advance(tokens);
	return (true);
}

static int	getfd_of_file(char *outfile, t_tokentype type)
{
	int	fd;

	if (type == REDIR_OUT)
		fd = ft_open(outfile, O_WRONLY | O_TRUNC | O_CREAT);
	else
		fd = ft_open(outfile, O_WRONLY | O_APPEND | O_CREAT);
	return (fd);
}

int	is_redir_token(t_list *token)
{
	t_tokentype	type;

	type = peek_type(token);
	return (type == REDIR_IN || type == REDIR_OUT || type == REDIR_OUT_APPEND
		|| type == HEREDOC);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:17:21 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/15 21:52:48 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	read_and_write_line_to_heredoc_file(t_list *tokens, int fd,
		int expanded);
static int	get_fd_of_heredoc_file(void);
static bool	label_is_quoted(char *label);

int	redir_heredoc(t_pipeline **plist, t_list **tokens, t_fds *fds)
{
	int		fd;
	bool	expanded;

	if (peek_type(*tokens) != WORD)
		return (print_syntax_error(*tokens), EOF);
	fd = get_fd_of_heredoc_file();
	if (fd == EOF)
		return (EOF);
	(*plist)->in_stream = fd;
	expanded = 0;
	if (label_is_quoted((char *)(*tokens)->content))
		expanded = 1;
	read_and_write_line_to_heredoc_file(*tokens, fd, expanded);
	advance(tokens);
	if (is_redir_token(*tokens))
		return (set_input_and_output_streams(plist, tokens, fds));
	return (true);
}

static int	get_fd_of_heredoc_file(void)
{
	char		*file;
	char		*nbr_str;
	int			fd;
	static int	nbr;

	while (true)
	{
		nbr_str = ft_itoa(nbr);
		file = ft_strdup("/tmp/.heredoc_");
		file = ft_strjoin(file, nbr_str);
		free(nbr_str);
		if (access(file, F_OK) == -1)
			break ;
		free(file);
		nbr++;
	}
	fd = ft_open(file, O_WRONLY | O_TRUNC | O_CREAT);
	ft_lstadd_back(&g_gbl.heredoc_files, ft_lstnew(file, WORD));
	return (fd);
}

static void	read_and_write_line_to_heredoc_file(t_list *tokens, int fd, int expanded)
{
	char	*label;
	char	*line;

	label = (char *)tokens->content;
	ft_fprintf(1, "> ");
	line = get_next_line(0);
	while (line)
	{
		if (is_end_of_heredoc(line, label))
			break ;
		if (expanded == 0)
			writeline_to_heredoc_file_with_expanding(line, fd);
		else
			writeline_to_heredoc_file_without_expanding(line, fd);
		free(line);
		ft_fprintf(1, "> ");
		line = get_next_line(0);
	}
	free(line);
}

static bool	label_is_quoted(char *label)
{
	return (*label == '\'' || *label == '"');
}

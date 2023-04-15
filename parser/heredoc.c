/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:17:21 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/15 15:35:08 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_fd_of_heredoc_file(void);
static void	read_and_write_line_to_heredoc_file(t_list *tokens, int fd,
		int expanded);
static void	writeline_to_heredoc_file_with_expanding(char *line, int fd);
static void	writeline_to_heredoc_file_without_expanding(char *line, int fd);
static bool	is_end_of_heredoc(char *line, char *label);
static bool	label_is_quoted(char *label);

char	*get_sub_sequence_of_heredoc(char **line);
static char	*get_quote_duplicate_and_advance_line(char **line);

int	redir_heredoc(t_pipeline **plist, t_list **tokens, t_fds *fds, int i)
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
	if (peek_type(*tokens) == HEREDOC)
		unlink_and_close_heredoc_file(*plist);
	if (is_redir_token(*tokens))
		return (set_input_and_output_streams(plist, tokens, fds, i));
	return (true);
}

static bool	label_is_quoted(char *label)
{
	return (*label == '\'' || *label == '"');
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
	g_gbl.heredoc_file = file;
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

static void	writeline_to_heredoc_file_without_expanding(char *line, int fd)
{
	size_t	len;

	len = ft_strlen(line);
	write(fd, line, len);
}

static void	writeline_to_heredoc_file_with_expanding(char *line, int fd)
{
	char	*expanded_line;
	char	*ptr;
	size_t	len;

	expanded_line = NULL;
	while (*line)
	{
		ptr = get_sub_sequence_of_heredoc(&line);
		if (ptr == NULL)
			continue ;
		expanded_line = ft_strjoin(expanded_line, ptr);
		free(ptr);
	}
	len = ft_strlen(expanded_line);
	write(fd, expanded_line, len);
	free(expanded_line);
}

char	*get_sub_sequence_of_heredoc(char **line)
{
	char	*sub_seq;

	sub_seq = NULL;
	if (**line == '\'' || **line == '"')
		return (get_quote_duplicate_and_advance_line(line));
	else if (**line == '$')
		sub_seq = find_variable_and_get_value(line);
	else
		sub_seq = get_word(line);
	return (sub_seq);
}

static char	*get_quote_duplicate_and_advance_line(char **line)
{
	char	quote_char;

	quote_char = **line;
	++*line;
	if (quote_char == '\'')
		return (ft_strdup("'"));
	return (ft_strdup("\""));
}

static bool	is_end_of_heredoc(char *line, char *label)
{
	char	*orig_label;
	size_t	line_len;
	size_t	label_len;

	orig_label = ft_strtrim(label, "'\"");
	line_len = ft_strlen(line);
	label_len = ft_strlen(orig_label);
	if (ft_strncmp(line, orig_label, line_len - 1) == 0 && line[line_len - 1] == '\n'
		&& line_len - 1 == label_len && line_len != 1)
		return (free(orig_label), true);
	return (free(orig_label), false);
}

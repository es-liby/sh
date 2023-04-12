/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 00:24:06 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/12 02:09:39 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	readline_from_heredoc(char *label, int fd);
static void	readline_without_expanding(char *label, int fd);
static void	readline_with_expanding(char *label, int fd);
static char	*expand_line(char *line);
static char	*runprompt_and_getline(void);
static void	write_line_to_heredoc_file(char *line, int fd);
static int	is_end_of_heredoc(char *line, char *label);
static char	*get_heredoc_file(void);

int	redir_heredoc(t_list **tokens)
{
	char	*label;
	char	*file;
	int		fd;

	if (peek_type(*tokens) != WORD)
		return (print_syntax_error(*tokens), EOF);
	label = (char *)(*tokens)->content;
	file = get_heredoc_file();
	fd = ft_open(file, O_WRONLY | O_TRUNC | O_CREAT);
	readline_from_heredoc(label, fd);
	if (ft_dup2(fd, 0) == -1)
		return (EOF);
	close(fd);
	unlink(file);
	free(file);
	advance(tokens);
	return (true);
}

static void	readline_from_heredoc(char *label, int fd)
{
	if (*label == '\'' || *label == '"')
		readline_without_expanding(label, fd);
	else
		readline_with_expanding(label, fd);
}

static void	readline_without_expanding(char *label, int fd)
{
	char	*line;
	char	*label_value;

	label_value = ft_strtrim(label, &(*label));
	line = runprompt_and_getline();
	while (line)
	{
		if (is_end_of_heredoc(line, label_value))
			break ;
		write_line_to_heredoc_file(line, fd);
		free(line);
		line = runprompt_and_getline();
	}
	free(line);
	free(label_value);
}

static void	readline_with_expanding(char *label, int fd)
{
	char	*line;
	char	*expanded_line;

	line = runprompt_and_getline();
	while (line)
	{
		if (is_end_of_heredoc(line, label))
			break ;
		expanded_line = expand_line(line);
		free(line);
		write_line_to_heredoc_file(expanded_line, fd);
		free(expanded_line);
		line = runprompt_and_getline();
	}
	free(line);
}

static char	*expand_line(char *line)
{
	char	*expanded_line;
	char	*sub_seq;

	expanded_line = NULL;
	while (*line)
	{
		sub_seq = get_sub_sequence(&line);
		if (sub_seq == NULL)
			continue ;
		expanded_line = ft_strjoin(expanded_line, sub_seq);
		free(sub_seq);
	}
	return (expanded_line);
}

static char	*runprompt_and_getline(void)
{
	char	*line;

	ft_fprintf(1, "> ");
	line = get_next_line(0);
	return (line);
}

static void	write_line_to_heredoc_file(char *line, int fd)
{
	size_t	size;

	size = ft_strlen(line);
	write(fd, line, size);
}

static int	is_end_of_heredoc(char *line, char *label)
{
	size_t	len;

	len = ft_strlen(label);
	if (ft_strncmp(line, label, len - 1) == 0 && line[len] == '\n')
		return (true);
	return (false);
}

static char	*get_heredoc_file(void)
{
	static int	nbr;
	char		*nbr_str;
	char		*file;

	while (true)
	{
		file = ft_strdup("/tmp/heredoc_");
		nbr_str = ft_itoa(nbr);
		file = ft_strjoin(file, nbr_str);
		free(nbr_str);
		if (access(file, F_OK) != 0)
			break ;
		nbr++;
		free(file);
	}
	return (file);
}

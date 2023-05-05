/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readlines_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:40:06 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 08:23:57 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	writeline_to_heredoc_file(char *line, int fd, int expanded);
static bool	is_end_of_heredoc(char *line, char *label);
static char	*get_orig_delim(char *label);
static char	*get_delim_word(char **label);

int	read_and_write_line_to_heredoc_file(t_list *tokens, int fd, int expanded)
{
	char	*label;
	char	*line;

	label = (char *)tokens->lexeme;
	while (true)
	{
		handle_signals_for_heredoc();
		line = readline("> ");
		if (g_glob.sigint == ON)
			return (ft_close(fd), free(line), EOF);
		if (line == NULL || is_end_of_heredoc(line, label))
			break ;
		writeline_to_heredoc_file(line, fd, expanded);
		free(line);
	}
	return (free(line), true);
}

static void	writeline_to_heredoc_file(char *line, int fd, int expanded)
{
	if (expanded == 0)
		writeline_to_heredoc_file_with_expanding(line, fd);
	else
		writeline_to_heredoc_file_without_expanding(line, fd);
}

static bool	is_end_of_heredoc(char *line, char *label)
{
	char	*orig_label;

	if (*label == '\0')
		return (false);
	orig_label = get_orig_delim(label);
	if (!ft_strcmp(line, orig_label))
		return (free(orig_label), true);
	return (free(orig_label), false);
}

static char	*get_orig_delim(char *label)
{
	char	*orig_delim;
	char	*tmp;

	orig_delim = NULL;
	tmp = NULL;
	while (*label)
	{
		if (*label == '\'' || *label == '"')
			tmp = remove_quote(&label);
		else
			tmp = get_delim_word(&label);
		if (tmp == NULL)
			break ;
		orig_delim = ft_strjoin(orig_delim, tmp);
		free(tmp);
	}
	return (orig_delim);
}

static char	*get_delim_word(char **label)
{
	char	*word;
	size_t	len;

	len = 0;
	while ((*label)[len] && (*label)[len] != '\'' && (*label)[len] != '"')
		len++;
	word = ft_substr(*label, 0, len);
	*label += len;
	return (word);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:03:50 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 15:10:20 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_quote_duplicate_and_advance_line(char **line);

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

void	writeline_to_heredoc_file_without_expanding(char *line, int fd)
{
	size_t	len;

	len = ft_strlen(line);
	write(fd, line, len);
	write(fd, "\n", 1);
}

void	writeline_to_heredoc_file_with_expanding(char *line, int fd)
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
	write(fd, "\n", 1);
	free(expanded_line);
}

bool	is_end_of_heredoc(char *line, char *label)
{
	char	*orig_label;
	size_t	line_len;
	size_t	label_len;

	if (*label == '\0')
		return (false);
	orig_label = ft_strtrim(label, "'\"");
	if (*orig_label == '\0')
		return (false);
	line_len = ft_strlen(line);
	label_len = ft_strlen(orig_label);
	if (!ft_strcmp(line, orig_label))
		return (free(orig_label), true);
	return (free(orig_label), false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:39:14 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:39:15 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_quote_duplicate_and_advance_line(char **line);

void	writeline_to_heredoc_file_with_expanding(char *line, int fd)
{
	char	*expanded_line;
	char	*ptr;

	expanded_line = NULL;
	while (*line)
	{
		ptr = get_sub_sequence_of_heredoc(&line);
		if (ptr == NULL)
			continue ;
		expanded_line = ft_strjoin(expanded_line, ptr);
		free(ptr);
	}
	if (expanded_line != NULL)
		ft_fprintf(fd, "%s", expanded_line);
	write(fd, "\n", 1);
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

void	writeline_to_heredoc_file_without_expanding(char *line, int fd)
{
	if (*line != '\0')
		ft_fprintf(fd, "%s", line);
	write(fd, "\n", 1);
}

char	*remove_quote(char **label)
{
	char	*word;
	size_t	len;

	++*label;
	if (**label == '\0')
		return (NULL);
	len = 0;
	while ((*label)[len] && (*label)[len] != '\'' && (*label)[len] != '"')
		len++;
	word = ft_substr(*label, 0, len);
	*label += len;
	return (word);
}

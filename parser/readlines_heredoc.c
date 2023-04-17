/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readlines_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:58:44 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 17:38:44 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	writeline_to_heredoc_file(char *line, int fd, int expanded);
static bool	is_end_of_heredoc(char *line, char *label);

int	read_and_write_line_to_heredoc_file(t_list *tokens, int fd, int expanded)
{
	char	*label;
	char	*line;

	label = (char *)tokens->lexeme;
	while (true)
	{
		handle_signals_for_heredoc();
		line = readline("> ");
		if (line == NULL)
			break ;
		if (g_gbl.sigint == ON)
			return (free(line), EOF);
		if (is_end_of_heredoc(line, label))
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
	orig_label = ft_strtrim(label, "'\"");
	if (!ft_strcmp(line, orig_label))
		return (free(orig_label), true);
	return (free(orig_label), false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:02:59 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/24 12:03:00 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	label_is_quoted(char *label);
static char	*get_heredoc_file(int *fd);
static void	set_heredoc_file(char *file);

int	readlines_from_heredoc_prompt(t_pipeline **plist, t_list **tokens)
{
	char	*file;
	int		expanded;
	int		fd;

	if (peek_type(*tokens) != WORD)
		return (syn_err(*tokens), EOF);
	file = get_heredoc_file(&fd);
	if (file == NULL)
		return (EOF);
	set_heredoc_file(file);
	expanded = label_is_quoted((char *)(*tokens)->lexeme);
	if (read_and_write_line_to_heredoc_file(*tokens, fd, expanded) == EOF)
		return (EOF);
	ft_close(fd);
	fd = ft_open(file, O_RDONLY);
	if (fd == EOF)
		return (free(g_gbl.heredoc_file), EOF);
	(*plist)->in_stream = fd;
	advance(tokens);
	if (is_redir_token(*tokens))
		return (set_input_and_output_streams(plist, tokens));
	return (true);
}

static char	*get_heredoc_file(int *fd)
{
	char		*file;
	char		*nbr_str;
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
	*fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0777);
	if (*fd == -1)
		return (perror("open"), free(file), NULL);
	return (file);
}

static void	set_heredoc_file(char *file)
{
	if (g_gbl.heredoc_file == NULL)
		g_gbl.heredoc_file = file;
	else
	{
		unlink(g_gbl.heredoc_file);
		free(g_gbl.heredoc_file);
		g_gbl.heredoc_file = file;
	}
}

static bool	label_is_quoted(char *label)
{
	while (*label)
	{
		if (*label == '\'' || *label == '"')
			return (true);
		++label;
	}
	return (false);
}

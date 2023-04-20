/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:17:21 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 18:15:22 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	label_is_quoted(char *label);
static char	*get_heredoc_file(int *fd);
static void	set_heredoc_file(t_pipeline *plist, char *file, int fd);

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
	expanded = label_is_quoted((char *)(*tokens)->lexeme);
	printf("read_and_write()\n");
	if (read_and_write_line_to_heredoc_file(*tokens, fd, expanded) == EOF)
		return (EOF);
	ft_close(fd);
	fd = ft_open(file, O_RDONLY);
	if (fd == EOF)
		return (free(g_gbl.heredoc_file), EOF);
	set_heredoc_file(*plist, file, fd);
	advance(tokens);
	if (is_redir_token(*tokens))
		return (set_input_and_output_streams(plist, tokens));
	printf("-----\n");
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

static void	set_heredoc_file(t_pipeline *plist, char *file, int fd)
{
	if (g_gbl.heredoc_file == NULL)
		g_gbl.heredoc_file = file;
	else
	{
		unlink(g_gbl.heredoc_file);
		free(g_gbl.heredoc_file);
		g_gbl.heredoc_file = file;
	}
	plist->in_stream = fd;
}

static bool	label_is_quoted(char *label)
{
	return (*label == '\'' || *label == '"');
}

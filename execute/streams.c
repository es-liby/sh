/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streams.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:00:14 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/25 14:02:50 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_dup(int fd);

int	duplicate_io_streams(t_pipeline *plist)
{
	if (plist->in_stream != 0)
		if (ft_dup2(plist->in_stream, STDIN_FILENO) == EOF)
			return (EOF);
	if (plist->out_stream != 1)
		if (ft_dup2(plist->out_stream, STDOUT_FILENO) == EOF)
			return (EOF);
	return (true);
}

void	dup_streams(t_pipeline *plist, int *stdin_dup, int *stdout_dup)
{
	if (plist->in_stream != 0)
	{
		*stdin_dup = ft_dup(STDIN_FILENO);
		ft_dup2(plist->in_stream, STDIN_FILENO);
	}
	if (plist->out_stream != 1)
	{
		*stdout_dup = ft_dup(STDOUT_FILENO);
		ft_dup2(plist->out_stream, STDOUT_FILENO);
	}
}

void	getback_io_streams(t_pipeline *plist, int stdin_dup, int stdout_dup)
{
	if (plist->in_stream != 0)
	{
		ft_dup2(stdin_dup, STDIN_FILENO);
		ft_close(stdin_dup);
	}
	if (plist->out_stream != 1)
	{
		ft_dup2(stdout_dup, STDOUT_FILENO);
		ft_close(stdout_dup);
	}
}

int	close_streams(t_pipeline *plist)
{
	while (plist)
	{
		if (plist->in_stream != 0)
			ft_close(plist->in_stream);
		if (plist->out_stream != 1)
			ft_close(plist->out_stream);
		plist = plist->next;
	}
	clear_pipes(g_gbl.fds);
	return (true);
}

static int	ft_dup(int fd)
{
	int	fd_dup;

	fd_dup = dup(fd);
	if (fd_dup == -1)
		perror("bash: dup");
	return (fd_dup);
}

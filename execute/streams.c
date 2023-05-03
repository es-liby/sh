/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streams.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:33:32 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/05/02 22:23:35 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	duplicate_io_streams(t_pipeline *plist)
{
	if (plist->in_stream != STDIN_FILENO)
		if (ft_dup2(plist->in_stream, STDIN_FILENO) == EOF)
			return (EOF);
	if (plist->out_stream != STDOUT_FILENO)
		if (ft_dup2(plist->out_stream, STDOUT_FILENO) == EOF)
			return (EOF);
	return (true);
}

int	dup_streams(t_pipeline *plist, int *stdin_dup, int *stdout_dup)
{
	if (plist->in_stream != 0)
	{
		*stdin_dup = ft_dup(STDIN_FILENO);
		if (*stdin_dup == EOF)
			return (EOF);
		if (ft_dup2(plist->in_stream, STDIN_FILENO) == EOF)
			return (EOF);
	}
	if (plist->out_stream != 1)
	{
		*stdout_dup = ft_dup(STDOUT_FILENO);
		if (*stdout_dup == EOF)
			return (EOF);
		if (ft_dup2(plist->out_stream, STDOUT_FILENO) == EOF)
			return (EOF);
	}
	return (true);
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
	clear_pipes(g_glob.fds);
	return (true);
}

int	ft_dup(int fd)
{
	int	fd_dup;

	fd_dup = dup(fd);
	if (fd_dup == -1)
		perror("sh: dup");
	return (fd_dup);
}

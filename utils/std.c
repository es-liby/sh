/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 01:46:23 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/15 14:52:13 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_open(char *file, int flags)
{
	int	fd;

	if (flags == O_RDONLY)
		fd = open(file, flags);
	else
		fd = open(file, flags, 0644);
	if (fd == -1)
	{
		ft_fprintf(2, "bash: %s: %s\n", file, strerror(errno));
		g_gbl.exit_status = 1;
	}
	return (fd);
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}

void	ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	ft_close(int fd)
{
	if (close(fd) == -1)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

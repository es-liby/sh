/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 01:46:23 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 08:12:52 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_open(char *file, int flags)
{
	int	fd;

	if (flags == O_RDONLY)
		fd = open(file, O_RDONLY);
	else
		fd = open(file, flags, 0644);
	if (fd == -1)
	{
		ft_fprintf(2, "sh: %s: %s\n", file, strerror(errno));
		g_glob.exit_status = 1;
	}
	return (fd);
}

int	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		g_glob.exit_status = 1;
		return (perror("sh: dup2"), EOF);
	}
	return (true);
}

int	ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		g_glob.exit_status = 1;
		return (perror("sh: pipe"), EOF);
	}
	return (true);
}

int	ft_close(int fd)
{
	if (fd == -1)
		return (true);
	if (close(fd) == -1)
	{
		g_glob.exit_status = 1;
		return (perror("sh: close"), EOF);
	}
	return (true);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		g_glob.exit_status = 1;
		perror("sh: fork");
	}
	return (pid);
}

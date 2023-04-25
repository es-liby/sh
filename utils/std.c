/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 01:46:23 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/25 14:14:37 by iabkadri         ###   ########.fr       */
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
		update_exit_status(1);
	}
	return (fd);
}

int	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		return (perror("bash: dup2"), EOF);
	return (true);
}

int	ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
		return (perror("bash: pipe"), EOF);
	return (true);
}

int	ft_close(int fd)
{
	if (fd == -1)
		return (true);
	if (close(fd) == -1)
		return (perror("bash: close"), EOF);
	return (true);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("bash: fork");
	return (pid);
}

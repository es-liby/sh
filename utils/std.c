/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 01:46:23 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/11 01:51:20 by iabkadri         ###   ########.fr       */
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
		ft_fprintf(2, "bash: %s: %s\n", file, strerror(errno));
	return (fd);
}

int	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		perror("dup2");
		return(ERROR);
	}
	return (true);
}

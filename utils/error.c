/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:07:43 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/01 12:47:15 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	fatal(char *msg)
{
	ft_fprintf(2, "sh: %s\n", msg);
}

void	exit_with_errmsg(char *err_src, int errno_val, int exit_status)
{
	ft_fprintf(2, "sh: %s: %s\n", err_src, strerror(errno_val));
	exit(exit_status);
}

void	exit_usage_err(void)
{
	ft_fprintf(2, "%s ./minishell\n", USG_ERR_MSG);
	exit(EXIT_FAILURE);
}

void	cmd_notfound(char *cmd)
{
	ft_fprintf(2, "sh: %s: command not found\n", cmd);
}

void	no_such_file_or_dir(char *cmd)
{
	ft_fprintf(2, "sh: %s: No such file or directory\n", cmd);
}

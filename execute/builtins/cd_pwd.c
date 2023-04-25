/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:00:18 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/25 15:25:57 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	strerror_for_cd(char *directory, int errno_val);

int	cdcmd(char **args)
{
	char	cwdbuf[FILENAME_MAX];

	if (args[0] == NULL)
		if (chdir(getenv("HOME")) == -1)
			return (strerror_for_cd(args[0], errno), EOF);
	if (getcwd(cwdbuf, FILENAME_MAX) == NULL)
		return (strerror_for_cd(args[0], errno), EOF);
	if (chdir(args[0]) == -1)
		return (strerror_for_cd(args[0], errno), EOF);
	update_exit_status(0);
	return (true);
}

int	pwdcmd(char **args)
{
	char		cwdbuf[FILENAME_MAX];

	(void)args;
	getcwd(cwdbuf, FILENAME_MAX);
	ft_fprintf(1, "%s\n", cwdbuf);
	update_exit_status(0);
	return (true);
}

static void	strerror_for_cd(char *directory, int errno_val)
{
	ft_fprintf(2, "bash: %s: %s\n", directory, strerror(errno_val));
}

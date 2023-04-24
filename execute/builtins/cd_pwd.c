/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:00:18 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/24 14:13:28 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cdcmd(char **args)
{
	if (args[0] == NULL)
	{
		if (chdir(getenv("HOME")) == -1)
		{
			ft_fprintf(2, "bash: %s: %s\n", args[0], strerror(errno));
			return (EOF);
		}
	}
	else if (chdir(args[0]) == -1)
	{
		ft_fprintf(2, "bash: %s: %s\n", args[0], strerror(errno));
		return (EOF);
	}
	update_exit_status(0);
	return (true);
}

int	pwdcmd(char **args)
{
	char	cwdbuf[FILENAME_MAX];

	(void)args;
	if (getcwd(cwdbuf, FILENAME_MAX) == NULL)
	{
		ft_fprintf(2, "bash: %s\n", strerror(errno));
		return (EOF);
	}
	ft_fprintf(1, "%s\n", cwdbuf);
	update_exit_status(0);
	return (true);
}

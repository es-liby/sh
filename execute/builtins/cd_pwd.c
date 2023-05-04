/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 07:20:42 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 19:34:44 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	cd_to_home_directory(void);

int	cdcmd(char **args)
{
	if (!args[0])
		return (cd_to_home_directory());
	if (chdir(args[0]) == -1)
	{
		ft_fprintf(2, "sh: %s: No such file or directory\n", args[0]);
		g_glob.exit_status = 1;
		return (-1);
	}
	update_cwd(args[0]);
	g_glob.exit_status = 0;
	return (1);
}

int	pwdcmd(char **args)
{
	char	*cwd;

	(void)args;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = getenvvar_value("$PWD");
	printf("%s\n", cwd);
	free(cwd);
	return (1);
}

static int	cd_to_home_directory(void)
{
	char	*home_dir;

	home_dir = getenvvar_value("$HOME");
	if (!home_dir)
	{
		g_glob.exit_status = 1;
		return (fatal("cd: HOME not set"), -1);
	}
	if (chdir(home_dir) == -1)
		return (perror("sh: cd"), free(home_dir), -1);
	update_pwd_and_oldpwd(home_dir);
	return (1);
}

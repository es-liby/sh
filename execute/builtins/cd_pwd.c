/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 07:20:42 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 21:24:55 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	cd_to_home_directory(void);

void	cdcmd(char **args)
{
	if (!args[0])
	{
		cd_to_home_directory();
		return ;
	}
	if (chdir(args[0]) == -1)
	{
		ft_fprintf(2, "sh: %s: No such file or directory\n", args[0]);
		g_glob.exit_status = 1;
		return ;
	}
	update_cwd(args[0]);
	g_glob.exit_status = 0;
}

void	pwdcmd(char **args)
{
	char	*cwd;

	(void)args;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = getenvvar_value("$PWD");
	printf("%s\n", cwd);
	free(cwd);
}

static void	cd_to_home_directory(void)
{
	char	*home_dir;

	home_dir = getenvvar_value("$HOME");
	if (!home_dir)
	{
		g_glob.exit_status = 1;
		fatal("cd: HOME not set");
		return ;
	}
	if (chdir(home_dir) == -1)
	{
		perror("sh: cd");
		free(home_dir);
		return ;
	}
	update_pwd_and_oldpwd(home_dir);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 07:20:42 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/26 10:10:29 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	cd_to_home_directory(void);

int	cdcmd(char **args)
{
	if (args[0] == NULL)
		return (cd_to_home_directory());
	if (chdir(args[0]) == -1)
	{
		ft_fprintf(2, "sh: %s: No such file or directory\n", args[0]);
		return ( EOF);
	}
	update_cwd(args[0]);
	return (true);
}

int	pwdcmd(char **args)
{
	char	*cwd;

	(void)args;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		cwd = getenvvar_value("$PWD");
	printf("%s\n", cwd);
	free(cwd);
	return (true);
}

static int	cd_to_home_directory(void)
{
	char	*home_dir;

	home_dir = getenv("HOME");
	if (home_dir == NULL)
		return (fatal("bash: cd: HOME not set"), EOF);
	if (chdir(home_dir) == -1)
		return (perror("sh: cd"), EOF);
	update_pwd_and_oldpwd(home_dir);
	return (true);
}

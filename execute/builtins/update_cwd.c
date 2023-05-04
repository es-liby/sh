/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 10:09:44 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 21:16:49 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	env_update(char *envvar, char *cwd);
static char	*create_cwd(char *arg);

void	update_cwd(char *arg)
{
	char	*new_cwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		new_cwd = create_cwd(arg);
		update_pwd_and_oldpwd(new_cwd);
		fatal("cd: error retrieving current directory: getcwd: cannot access "
			"parent directories: No such file or directory");
		return ;
	}
	update_pwd_and_oldpwd(cwd);
}

void	update_pwd_and_oldpwd(char *cwd)
{
	char	*old_cwd;

	old_cwd = getenvvar_value("$PWD");
	env_update("OLDPWD", old_cwd);
	env_update("PWD", cwd);
}

static void	env_update(char *envvar, char *cwd)
{
	t_env	*envlist;

	envlist = g_glob.envlist;
	while (envlist)
	{
		if (ft_strcmp(envlist->key, envvar) == 0)
			break ;
		envlist = envlist->next;
	}
	if (!envlist)
	{
		add_envvar(&g_glob.envlist, ft_strdup(envvar), cwd);
		return ;
	}
	free(envlist->value);
	envlist->value = cwd;
}

static char	*create_cwd(char *arg)
{
	char	*cwd;
	char	*pwd;

	pwd = getenvvar_value("$PWD");
	cwd = ft_strjoin(pwd, "/");
	cwd = ft_strjoin(cwd, arg);
	return (cwd);
}

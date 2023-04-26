/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:00:18 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/25 18:21:35by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	strerror_for_cd(char *directory, int errno_val);
int			update_cwd_envvars(char *arg);
void		update_cwd(char *new_cwd);
void		update_oldpwd_and_pwd(char *envvar, char *cwd);
char		*create_new_cwd(char *arg);

int	cdcmd(char **args)
{
	if (args[0] == NULL)
	{
		if (chdir(getenv("HOME")) == -1)
			return (strerror_for_cd(args[0], errno), EOF);
	}
	else
	{
		if (chdir(args[0]) == -1)
		{
			if (errno != ENOENT)
				return (strerror_for_cd(args[0], errno), EOF);
			return (true);
		}
	}
	if (update_cwd_envvars(args[0]) == EOF)
		return (EOF);
	update_exit_status(0);
	return (true);
}

int	pwdcmd(char **args)
{
	t_env	*envlist;

	(void)args;
	envlist = g_gbl.envlist;
	while (envlist)
	{
		if (ft_strcmp(envlist->key, "PWD") == 0)
			break ;
		envlist = envlist->next;
	}
	if (envlist == NULL)
		return (ft_fprintf(1, "\n"), true);
	ft_fprintf(1, "%s\n", envlist->value);
	update_exit_status(0);
	return (true);
}

int	update_cwd_envvars(char *arg)
{
	char	*cwd;
	char	*new_cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		new_cwd = create_new_cwd(arg);
		update_cwd(new_cwd);
		ft_fprintf(2, "cd: error retrieving current directory: "
			"getcwd: cannot access parent directories: No such file or directory\n");
		return (EOF);
	}
	update_cwd(cwd);
	return (true);
}

char	*create_new_cwd(char *arg)
{
	char	*new_cwd;
	char	*old_path;

	old_path = getenvvar_value("$OLDPWD");
	new_cwd = ft_strjoin(old_path, "/");
	new_cwd = ft_strjoin(new_cwd, arg);
	return (new_cwd);
}

void	update_cwd(char *new_cwd)
{
	char	*old_cwd;

	old_cwd = getenvvar_value("$PWD");
	update_oldpwd_and_pwd("OLDPWD", old_cwd);
	update_oldpwd_and_pwd("PWD", new_cwd);
}

void	update_oldpwd_and_pwd(char *envvar, char *cwd)
{
	t_env	*envlist;

	envlist = g_gbl.envlist;
	while (envlist)
	{
		if (ft_strcmp(envlist->key, envvar) == 0)
			break ;
		envlist = envlist->next;
	}
	if (envlist == NULL)
		return ;
	free(envlist->value);
	envlist->value = cwd;
}

static void	strerror_for_cd(char *directory, int errno_val)
{
	ft_fprintf(2, "bash: %s: %s\n", directory, strerror(errno_val));
	update_exit_status(1);
}

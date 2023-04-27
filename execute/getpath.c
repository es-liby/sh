/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:05:21 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/27 10:20:02 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	path_entry_is_found(t_env *envlist);
static char	*get_path_for_cmd(char **path, char *cmd);
static char	*dup_and_join(char *path, char *cmd);

char	*getpath(char *cmd)
{
	t_env	*envlist;
	char	**path;
	char	*cmd_path;

	envlist = g_glob.envlist;
	while (envlist)
	{
		if (path_entry_is_found(envlist))
		{
			path = ft_split(envlist->value + 5, ':');
			break ;
		}
		envlist = envlist->next;
	}
	if (envlist == NULL)
		return (no_such_file_or_dir(cmd), update_exit_status(127), NULL);
	if (is_a_directory(cmd))
		return (cmd);
	cmd_path = get_path_for_cmd(path, cmd);
	return (free_tab(path), cmd_path);
}

static bool	path_entry_is_found(t_env *envlist)
{
	if (ft_strcmp(envlist->key, "PATH") == 0)
		return (true);
	return (false);
}

static char	*get_path_for_cmd(char **path, char *cmd)
{
	char	*cmd_path;
	int		i;

	cmd_path = NULL;
	i = -1;
	while (path[++i])
	{
		cmd_path = dup_and_join(path[i], cmd);
		if (access(cmd_path, X_OK) != -1)
			break ;
		free(cmd_path);
	}
	if (path[i] == NULL)
		return (cmd_notfound(cmd), update_exit_status(127), NULL);
	return (cmd_path);
}

static char	*dup_and_join(char *path, char *cmd)
{
	char	*cmd_path;
	char	*tmp_ptr;

	tmp_ptr = ft_strdup(path);
	tmp_ptr = ft_strjoin(tmp_ptr, "/");
	cmd_path = ft_strjoin(tmp_ptr, cmd);
	return (cmd_path);
}

int	is_a_directory(char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) == -1)
		return (false);
	if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
		return (true);
	return (false);
}

#include <minishell.h>

static int	is_a_directory(char *cmd);
static char	*getpath(char *cmd);
static bool	path_entry_is_found(t_env *envlist);
static char	*get_path_for_cmd(char **path, char *cmd);

int	is_a_path_or_a_directory(char *cmd);
int	is_a_path(char *cmd);

int	search_and_set_path_for_cmds(t_pipeline *plist)
{
	char	*cmd_path;

	if (is_a_path_or_a_directory(plist->cmd))
		return (true);
	cmd_path = getpath(plist->cmd);
	if (cmd_path == NULL)
		return (EOF);
	free(plist->cmd);
	plist->cmd = cmd_path;
	return (true);
}

int	is_a_path_or_a_directory(char *cmd)
{
	return (is_a_path(cmd) || is_a_directory(cmd));
}

int	is_a_path(char *cmd)
{
	return (*cmd == '.' || *cmd == '/');
}

static int	is_a_directory(char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) == -1)
		return (false);
	if ((statbuf.st_mode & __S_IFMT) == __S_IFDIR)
		return (true);
	return (false);
}

static char	*getpath(char *cmd)
{
	t_env	*envlist;
	char	**path;
	char	*cmd_path;

	envlist = g_gbl.envlist;
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
	{
		ft_fprintf(2, "bash: %s: command not found\n", cmd);
		return (NULL);
	}
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
	char	*path_ptr;
	int		i;

	cmd_path = NULL;
	i = -1;
	path_ptr = NULL;
	while (path[++i])
	{
		path_ptr = ft_strdup(path[i]);
		path_ptr = ft_strjoin(path_ptr, "/");
		cmd_path = ft_strjoin(path_ptr, cmd);
		if (access(cmd_path, X_OK) != -1)
			break ;
		free(cmd_path);
	}
	if (path[i] == NULL)
	{
		ft_fprintf(2, "bash: %s: command not found\n", cmd);
		return (NULL);
	}
	return (cmd_path);
}

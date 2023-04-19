#include <minishell.h>

static char	*getpath(char *cmd);
static bool	path_entry_is_found(t_list *envlist);
static char	*get_path_for_cmd(char **path, char *cmd);

int	search_and_set_path_for_cmds(t_pipeline *plist)
{
	char	*cmd_path;
	char	*path;

	while (plist)
	{
		path = getpath(plist->cmd);
		if (path == NULL)
			return (EOF);
		cmd_path = ft_strjoin(path, plist->cmd);
		free(plist->cmd);
		plist->cmd = cmd_path;
		plist = plist->next;
	}
	return (true);
}

static char	*getpath(char *cmd)
{
	t_list	*envlist;
	char	**path;
	char	*cmd_path;

	envlist = g_gbl.envlist;
	while (envlist)
	{
		if (path_entry_is_found(envlist))
		{
			path = ft_split(envlist->lexeme + 5, ':');
			break ;
		}
		advance(&envlist);
	}
	if (envlist == NULL)
	{
		ft_fprintf(2, "bash: %s: command not found\n", cmd);
		return (NULL);
	}
	cmd_path = get_path_for_cmd(path, cmd);
	return (free_tab(path), cmd_path);
}

static bool	path_entry_is_found(t_list *envlist)
{
	if (ft_strncmp(envlist->lexeme, "PATH=", 5) == 0)
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
		cmd_path = ft_strjoin(path[i], cmd);
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

#include <minishell.h>

static int	is_a_directory(char *cmd);
static char	*getpath(char *cmd);
static bool	path_entry_is_found(t_list *envlist);
static char	*get_path_for_cmd(char **path, char *cmd);

int	search_and_set_path_for_cmds(t_pipeline *plist)
{
	char	*cmd_path;
	int		ret_val;

	while (plist)
	{
		ret_val = is_a_directory(plist->cmd);
		if (ret_val == EOF)
			return (EOF);
		if (ret_val == true)
		{
			plist = plist->next;
			continue ;
		}
		cmd_path = getpath(plist->cmd);
		if (cmd_path == NULL)
			return (EOF);
		free(plist->cmd);
		plist->cmd = cmd_path;
		plist = plist->next;
	}
	return (true);
}

static int	is_a_directory(char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) == -1)
		return (EOF);
	if ((statbuf.st_mode & __S_IFMT) == __S_IFDIR)
		return (true);
	return (false);
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
	if (is_a_directory(cmd))
		return (cmd);
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

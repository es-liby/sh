#include <minishell.h>

static void	executecmd(t_pipeline *plist);
static bool	is_a_directory(char *cmd);

int	execute(t_pipeline *plist)
{
	pid_t		pid;
	int			i;
	int			status;
	t_builtin	cmdtype;

	i = 0;
	while (plist)
	{
		cmdtype = is_a_builtin_cmd(plist->cmd);
		if (cmdtype != NONE)
		{
			if (execute_builtin_cmd(plist, cmdtype) == EOF)
				return (EOF);
			plist = plist->next;
			i++;
			continue ;
		}
		pid = ft_fork();
		if (pid == -1)
			return (EOF);
		if (pid == 0)
			executecmd(plist);
		if (close_write_end(i) == EOF)
			return (EOF);
		waitpid(pid, &status, 0);
		plist = plist->next;
		i++;
	}
	g_gbl.exit_status = status;
	return (close_read_ends(g_gbl.fds));
}

static void	executecmd(t_pipeline *plist)
{
	char		*cmd;
	char		**args;

	if (ft_dup2(plist->in_stream, STDIN_FILENO) == EOF)
		exit(EXIT_FAILURE);
	if (ft_dup2(plist->out_stream, STDOUT_FILENO) == EOF)
		exit(EXIT_FAILURE);
	if (close_streams(plist) == EOF)
		exit(EXIT_FAILURE);
	if (search_and_set_path_for_cmds(plist) == EOF)
		exit(EXIT_FAILURE);
	cmd = plist->cmd;
	args = plist->args;
	if (is_a_directory(cmd))
	{
		ft_fprintf(2, "bash: %s: Is a directory\n", cmd);
		exit(126);
	}
	execve(cmd, args, g_gbl.envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

static bool	is_a_directory(char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) == -1)
	{
		ft_fprintf(2, "bash: %s: %s\n", cmd, strerror(errno));
		exit(EXIT_FAILURE);
	}
	if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
		return (true);
	return (false);
}

void	error(char *msg)
{
	ft_fprintf(2, "%s\n", msg);
}

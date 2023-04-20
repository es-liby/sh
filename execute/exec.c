#include <minishell.h>

static void	executecmd(t_pipeline *plist);
void		close_write_end(int i);
void		close_read_ends(t_fds *fds);

bool	is_a_directory(char *cmd);

int	execute(t_pipeline *plist)
{
	pid_t		pid;
	int			i;
	int			status;

	i = 0;
	// printplist(plist);
	while (plist)
	{
		pid = ft_fork();
		if (pid == -1)
			return (EOF);
		if (pid == 0)
			executecmd(plist);
		close_write_end(i);
		waitpid(pid, &status, 0);
		plist = plist->next;
		i++;
	}
	g_gbl.exit_status = status;
	close_read_ends(g_gbl.fds);
	return (true);
}

static void	executecmd(t_pipeline *plist)
{
	char	*cmd;
	char	**args;

	ft_dup2(plist->in_stream, STDIN_FILENO);
	ft_dup2(plist->out_stream, STDOUT_FILENO);
	close_streams(plist);
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

bool	is_a_directory(char *cmd)
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

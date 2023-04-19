#include <minishell.h>

static void	executecmd(t_pipeline *plist, t_pipeline *plist_ptr);
void		close_write_end(int i);
void		close_read_ends(t_fds *fds);

int	execute(t_pipeline *plist)
{
	t_pipeline	*plist_ptr;
	pid_t		pid;
	int			i;
	int			status;

	i = 0;
	plist_ptr = plist;
	while (plist)
	{
		pid = ft_fork();
		if (pid == -1)
			return (EOF);
		if (pid == 0)
			executecmd(plist, plist_ptr);
		close_write_end(i);
		waitpid(pid, &status, 0);
		if (status != 0)
			return (g_gbl.exit_status = status, EOF);
		plist = plist->next;
		i++;
	}
	close_read_ends(g_gbl.fds);
	return (true);
}

void	close_write_end(int i)
{
	if (g_gbl.fds == NULL)
		return ;
	if (i == 0)
		return ;
	ft_close(g_gbl.fds->fds[i - 1][1]);
	g_gbl.fds->fds[i - 1][1] = -1;
}

void	close_read_ends(t_fds *fds)
{
	int	i;

	if (fds == NULL)
		return ;
	i = -1;
	while (++i < fds->n)
		ft_close(fds->fds[i][0]);
	clear_pipes();
}

bool	is_not_pipe_fd(int fd)
{
	t_fds	*fds;
	int		i;

	fds = g_gbl.fds;
	if (fds == NULL)
		return (true);
	i = -1;
	while (++i < fds->n)
	{
		if (fd == fds->fds[i][0] || fd == fds->fds[i][1])
			return (false);
	}
	return (true);
}

void	close_streams(t_pipeline *plist)
{
	if (plist->in_stream != 0)
		if (is_not_pipe_fd(plist->in_stream))
			ft_close(plist->in_stream);
	if (plist->out_stream != 1)
		if (is_not_pipe_fd(plist->out_stream))
			ft_close(plist->out_stream);
	close_pipes();
}

static void	executecmd(t_pipeline *plist, t_pipeline *plist_ptr)
{
	char	*cmd;
	char	**args;
	char	**envlist;

	(void)plist_ptr;
	cmd = plist->cmd;
	args = plist->args;
	ft_dup2(plist->in_stream, 0);
	ft_dup2(plist->out_stream, 1);
	close_streams(plist);
	envlist = get_envlist();
	// if (is_a_file(cmd))
	// 	execute_filecmd(cmd, args, envlist);
	execve(cmd, args, envlist);
	perror("execve");
	exit(EXIT_FAILURE);
}

char	**get_envlist(void)
{
	char	**envlist;
	t_list	*env_ptr;
	size_t	size;
	int		indx;

	env_ptr = g_gbl.envlist;
	size = ft_lstsize(env_ptr);
	envlist = ft_calloc(size + 1, sizeof(char *));
	indx = -1;
	while (env_ptr)
	{
		envlist[++indx] = ft_strdup((char *)env_ptr->lexeme);
		advance(&env_ptr);
	}
	envlist[indx] = NULL;
	return (envlist);
}

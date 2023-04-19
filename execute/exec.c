#include <minishell.h>

static void	executecmd(t_pipeline *plist);
static void	close_streams(t_pipeline *plist);

int	execute(t_pipeline *plist)
{
	int		pid;
	t_ids	*ids;

	ids = NULL;
	while (plist)
	{
		pid = ft_fork();
		if (pid == -1)
			return (EOF);
		if (pid == 0)
			executecmd(plist);
		addid(ids, pid);
		plist = plist->next;
	}
	close_streams(plist);
	wait_ids(ids);
	return (true);
}

static void	executecmd(t_pipeline *plist)
{
	char	*cmd;
	char	**args;
	char	**envlist;

	cmd = plist->cmd;
	args = plist->args;
	ft_dup2(plist->in_stream, 0);
	ft_dup2(plist->out_stream, 1);
	close_streams(plist);
	envlist = get_envlist();
	execve(cmd, args, envlist);
	perror("execve");
	exit(EXIT_FAILURE);
}

static void	close_streams(t_pipeline *plist)
{
	while (plist)
	{
		ft_close(plist->in_stream);
		ft_close(plist->out_stream);
		plist = plist->next;
	}
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

#include <minishell.h>

static bool	is_not_pipe_fd(int fd);

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
	{
		if (fds->fds[i][0] != -1)
			ft_close(fds->fds[i][0]);
		fds->fds[i][0] = -1;
	}
	clear_pipes();
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

static bool	is_not_pipe_fd(int fd)
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

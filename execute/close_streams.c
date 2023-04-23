#include <minishell.h>

int	close_write_end(int i)
{
	if (g_gbl.fds == NULL)
		return (true);
	if (i == 0)
		return (true);
	if (ft_close(g_gbl.fds->fds[i - 1][1]) == EOF)
		return (EOF);
	g_gbl.fds->fds[i - 1][1] = -1;
	return (true);
}

int	close_read_ends(t_fds *fds)
{
	int	i;

	if (fds == NULL)
		return (true);
	i = -1;
	while (++i < fds->n)
	{
		if (fds->fds[i][0] != -1)
			if (ft_close(fds->fds[i][0]) == EOF)
				return (EOF);
		fds->fds[i][0] = -1;
	}
	clear_pipes(fds);
	return (true);
}

int	close_streams(t_pipeline *plist)
{
	if (plist->in_stream != 0)
	{
		if (is_not_pipe_fd(plist->in_stream))
		{
			if (ft_close(plist->in_stream) == EOF)
				return (EOF);
		}
	}
	if (plist->out_stream != 1)
	{
		if (is_not_pipe_fd(plist->out_stream))
		{
			if (ft_close(plist->out_stream) == EOF)
				return (EOF);
		}
	}
	return (close_pipes());
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

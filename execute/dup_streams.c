#include <minishell.h>

static int	ft_dup(int fd);

int	dup_streams(t_pipeline *plist, int *stdin_dup, int *stdout_dup)
{
	if (plist->in_stream != 0)
	{
		*stdin_dup = ft_dup(STDIN_FILENO);
		if (*stdin_dup == -1)
			return (EOF);
		if (ft_dup2(plist->in_stream, STDIN_FILENO) == EOF)
			return (EOF);
		if (is_not_pipe_fd(plist->in_stream))
			if (ft_close(plist->in_stream) == EOF)
				return (EOF);
	}
	if (plist->out_stream != 1)
	{
		*stdout_dup = ft_dup(STDOUT_FILENO);
		if (*stdout_dup == -1)
			return (EOF);
		if (ft_dup2(plist->out_stream, STDOUT_FILENO) == EOF)
			return (EOF);
		if (is_not_pipe_fd(plist->out_stream))
			if (ft_close(plist->out_stream) == EOF)
				return (EOF);
	}
	return (true);
}

int	getback_io_streams(t_pipeline *plist, int stdin_dup, int stdout_dup)
{
	if (plist->in_stream != 0)
	{
		if (ft_dup2(stdin_dup, STDIN_FILENO) == EOF)
			return (EOF);
		if (ft_close(stdin_dup) == EOF)
			return (EOF);
	}
	if (plist->out_stream != 1)
	{
		if (ft_dup2(stdout_dup, STDOUT_FILENO) == EOF)
			return (EOF);
		if (ft_close(stdout_dup) == EOF)
			return (EOF);
	}
	return (true);
}

static int	ft_dup(int fd)
{
	int	fd_dup;

	fd_dup = dup(fd);
	if (fd_dup == -1)
		perror("bash: dup");
	return (fd_dup);
}

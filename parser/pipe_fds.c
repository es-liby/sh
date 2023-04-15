#include <minishell.h>

static t_fds	*alloc_fds_of_pipe(int n);
static void		open_pipes(int **fds, int n);

t_fds	*count_and_open_pipes(t_list *tokens)
{
	t_fds	*fds;
	int		n;

	n = 0;
	while (tokens)
	{
		if (peek_type(tokens) == PIPE)
			n++;
		advance(&tokens);
	}
	fds = alloc_fds_of_pipe(n);
	open_pipes(fds->fds, n);
	return (fds);
}

static t_fds	*alloc_fds_of_pipe(int n)
{
	t_fds	*fds;
	int		i;

	fds = ft_calloc(1, sizeof(t_fds));
	fds->fds = ft_calloc(n, sizeof(int *));
	i = -1;
	while (++i < n)
		fds->fds[i] = ft_calloc(2, sizeof(int));
	fds->n = n;
	return (fds);
}

static void	open_pipes(int **fds, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		ft_pipe(fds[i]);
}

void	close_pipes(t_fds *fds)
{
	int	i;

	if (fds == NULL)
		return ;
	i = -1;
	while (++i < fds->n)
	{
		ft_close(fds->fds[i][0]);
		ft_close(fds->fds[i][1]);
	}
	clear_pipes(fds);
}

void	clear_pipes(t_fds *fds)
{
	int	i;

	if (fds == NULL)
		return ;
	i = -1;
	while (++i < fds->n)
		free(fds->fds[i]);
	free(fds->fds);
	free(fds);
}

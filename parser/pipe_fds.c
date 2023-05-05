/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:39:40 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:39:41 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_fds	*alloc_fds_of_pipe(int n);

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
	if (open_pipes(fds->fds, n) == EOF)
		return (clear_pipes(fds), NULL);
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
	fds->pipe_counter = 0;
	return (fds);
}

int	open_pipes(int **fds, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (ft_pipe(fds[i]) == EOF)
			return (EOF);
	}
	return (true);
}

int	close_pipes(void)
{
	t_fds	*fds;
	int		i;

	fds = g_glob.fds;
	if (fds == NULL)
		return (true);
	i = -1;
	while (++i < fds->n)
	{
		if (fds->fds[i][0] != -1)
			if (ft_close(fds->fds[i][0]) == EOF)
				return (EOF);
		if (fds->fds[i][1] != -1)
			if (ft_close(fds->fds[i][1]) == EOF)
				return (EOF);
		fds->fds[i][0] = -1;
		fds->fds[i][1] = -1;
	}
	clear_pipes(fds);
	return (true);
}

void	clear_pipes(t_fds *fds)
{
	int		i;

	if (fds == NULL)
		return ;
	i = -1;
	while (++i < fds->n)
		free(fds->fds[i]);
	free(fds->fds);
	free(fds);
	g_glob.fds = NULL;
}

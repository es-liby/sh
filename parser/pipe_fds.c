/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:01:27 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 18:01:28 by iabkadri         ###   ########.fr       */
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
	fds->pipe_counter = 0;
	return (fds);
}

void	open_pipes(int **fds, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		ft_pipe(fds[i]);
}

void	close_pipes(void)
{
	t_fds	*fds;
	int		i;

	fds = g_gbl.fds;
	if (fds == NULL)
		return ;
	i = -1;
	while (++i < fds->n)
	{
		ft_close(fds->fds[i][0]);
		ft_close(fds->fds[i][1]);
	}
}

void	clear_pipes(void)
{
	t_fds	*fds;
	int		i;

	fds = g_gbl.fds;
	if (fds == NULL)
		return ;
	i = -1;
	while (++i < fds->n)
		free(fds->fds[i]);
	free(fds->fds);
	free(fds);
	g_gbl.fds = NULL;
}

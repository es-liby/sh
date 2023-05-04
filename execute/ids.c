/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ids.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:33:14 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/05/04 16:31:18 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_ids	*last_id(t_ids *ids);
static void		clear_ids(t_ids **ids);

void	add_id(t_ids **ids, pid_t pid)
{
	t_ids	*tmp;

	if (!(*ids))
	{
		*ids = ft_calloc(1, sizeof(t_ids));
		(*ids)->pid = pid;
		(*ids)->next_id = NULL;
		return ;
	}
	tmp = NULL;
	add_id(&tmp, pid);
	last_id(*ids)->next_id = tmp;
}

void	wait_pids_and_update_exit_status(t_ids **ids)
{
	t_ids	*ids_ptr;
	int		status;

	if (!(*ids))
		return ;
	ids_ptr = *ids;
	while (ids_ptr)
	{
		waitpid(ids_ptr->pid, &status, 0);
		ids_ptr = ids_ptr->next_id;
	}
	update_exit_status(status);
	clear_ids(ids);
}

static t_ids	*last_id(t_ids *ids)
{
	while (ids && ids->next_id)
		ids = ids->next_id;
	return (ids);
}

static void	clear_ids(t_ids **ids)
{
	t_ids	*tmp_ptr;

	while (*ids)
	{
		tmp_ptr = *ids;
		*ids = (*ids)->next_id;
		free(tmp_ptr);
	}
}

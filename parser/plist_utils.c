/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plist_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:39:45 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:39:46 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_pipeline	*new_plist(void)
{
	t_pipeline	*plist;

	plist = ft_calloc(1, sizeof(t_pipeline));
	plist->cmd = NULL;
	plist->args = NULL;
	plist->in_stream = 0;
	plist->out_stream = 1;
	plist->next = NULL;
	return (plist);
}

void	addback(t_pipeline **plist, t_pipeline *new)
{
	if (*plist == NULL)
		*plist = new;
	else
		last_plist(*plist)->next = new;
}

t_pipeline	*last_plist(t_pipeline *plist)
{
	while (plist && plist->next)
		plist = plist->next;
	return (plist);
}

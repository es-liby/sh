/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plist_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:15:31 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/15 17:15:35 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

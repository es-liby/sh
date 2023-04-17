/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:51:08 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 18:04:25 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	clear_plist(t_pipeline **plist)
{
	t_pipeline	*tmp;

	while (*plist)
	{
		tmp = *plist;
		*plist = (*plist)->next;
		free(tmp->cmd);
		free(tmp->args);
		free(tmp);
	}
}

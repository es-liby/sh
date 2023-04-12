/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:39:59 by iabkadri          #+#    #+#             */
/*   Updated: 2023/01/09 10:38:37 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_lstsize(t_list *stk)
{
	int	nnode;

	nnode = 0;
	while (stk != NULL)
	{
		nnode++;
		stk = stk->next;
	}
	return (nnode);
}

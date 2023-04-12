/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:48:39 by iabkadri          #+#    #+#             */
/*   Updated: 2023/01/09 10:35:24 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstclear(t_list **stk, void (*del)(void *))
{
	t_list	*prev;

	while (*stk != NULL)
	{
		prev = *stk;
		*stk = (*stk)->next;
		ft_lstdelone(prev, del);
	}
}

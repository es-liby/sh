/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 10:47:05 by iabkadri          #+#    #+#             */
/*   Updated: 2023/01/14 10:47:06 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstadd_back(t_list **stk, t_list *new)
{
	t_list	*last;

	if (*stk == NULL)
		*stk = new;
	else
	{
		last = ft_lstlast(*stk);
		ft_lstlast(*stk)->next = new;
		new->prev = last;
	}
}

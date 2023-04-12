/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:36:33 by iabkadri          #+#    #+#             */
/*   Updated: 2023/01/13 12:19:27 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstadd_front(t_list **stk, t_list *new)
{
	if (new == NULL)
		return ;
	if (*stk != NULL)
		(*stk)->prev = new;
	new->next = *stk;
	new->prev = NULL;
	*stk = new;
}

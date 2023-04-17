/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:38:27 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 15:27:21 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *stk, void *(*f)(void *), void (*del)(void *))
{
	t_list	*header;
	t_list	*new;

	header = NULL;
	while (stk != NULL)
	{
		new = ft_lstnew((*f)(stk->lexeme), -1);
		if (new == NULL)
		{
			ft_lstclear(&header, del);
			break ;
		}
		ft_lstadd_back(&header, new);
		stk = stk->next;
	}
	return (header);
}

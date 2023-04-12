/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:53:55 by iabkadri          #+#    #+#             */
/*   Updated: 2023/01/09 10:36:13 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstiter(t_list *stk, void (*f)(void *))
{
	if (stk == NULL)
		return ;
	(*f)(stk->content);
	ft_lstiter(stk->next, f);
}

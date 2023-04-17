/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:53:55 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 15:26:35 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstiter(t_list *stk, void (*f)(void *))
{
	if (stk == NULL)
		return ;
	(*f)(stk->lexeme);
	ft_lstiter(stk->next, f);
}

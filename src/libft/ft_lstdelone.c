/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:11:15 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 15:26:23 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstdelone(t_list *stk, void (*del)(void *))
{
	if (stk == NULL || del == NULL)
		return ;
	(*del)(stk->lexeme);
	free(stk);
}

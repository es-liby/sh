/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:11:15 by iabkadri          #+#    #+#             */
/*   Updated: 2023/01/09 10:35:52 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstdelone(t_list *stk, void (*del)(void *))
{
	if (stk == NULL || del == NULL)
		return ;
	(*del)(stk->content);
	free(stk);
}

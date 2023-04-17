/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:18:08 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 15:27:43 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstnew(void *lexeme, t_tokentype type)
{
	t_list	*new_node;

	new_node = ft_calloc(1, sizeof(t_list));
	new_node->lexeme = lexeme;
	new_node->type = type;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

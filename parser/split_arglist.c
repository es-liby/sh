/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arglist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:37:38 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:37:39 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**split_arglist(t_list *arglist)
{
	char	**args_sp;
	size_t	size;
	size_t	indx;

	size = ft_lstsize(arglist) + 1;
	args_sp = ft_calloc(size, sizeof(char *));
	indx = 0;
	while (arglist)
	{
		args_sp[indx++] = ft_strdup((char *)arglist->lexeme);
		advance(&arglist);
	}
	args_sp[indx] = NULL;
	return (args_sp);
}

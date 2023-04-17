/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:22:32 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 11:22:03 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	syn_err(t_list *tokens)
{
	char	*content;

	if (tokens == NULL)
	{
		ft_fprintf(2, "bash: syntax error near unexpected token `newline'\n");
		return ;
	}
	content = (char *)tokens->content;
	ft_fprintf(2, "bash: syntax error near unexpected token `%s'\n", content);
}

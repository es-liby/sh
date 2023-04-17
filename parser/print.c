/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:22:32 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 15:29:49 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	syn_err(t_list *tokens)
{
	char	*lexeme;

	if (tokens == NULL)
	{
		ft_fprintf(2, "bash: syntax error near unexpected token `newline'\n");
		return ;
	}
	lexeme = (char *)tokens->lexeme;
	ft_fprintf(2, "bash: syntax error near unexpected token `%s'\n", lexeme);
}

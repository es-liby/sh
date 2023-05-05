/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:39:50 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:39:51 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	syn_err(t_list *tokens)
{
	char	*lexeme;

	g_glob.exit_status = 258;
	if (tokens == NULL)
	{
		ft_fprintf(2, "sh: syntax error near unexpected token `newline'\n");
		return ;
	}
	lexeme = (char *)tokens->lexeme;
	ft_fprintf(2, "sh: syntax error near unexpected token `%s'\n", lexeme);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:22:32 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/15 18:23:13 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_syntax_error(t_list *tokens)
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

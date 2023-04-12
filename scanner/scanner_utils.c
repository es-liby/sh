/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:24:52 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/11 22:57:48 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	addtoken(t_list **tokens, char *lexeme, t_tokentype type)
{
	t_list	*new_token;

	new_token = ft_lstnew(lexeme, type);
	ft_lstadd_back(tokens, new_token);
}

int	s_match(char **ptr, char c)
{
	if (**ptr != c)
		return (false);
	++*ptr;
	return (true);
}

int	isopt(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '$');
}

int	ft_isblank(char c)
{
	return (c == ' ' || c == '\t');
}

int	check_for_syntax_error(char *pipeline)
{
	while (*pipeline)
	{
		if (operator_not_supported(*pipeline) == true)
			return (EOF);
		pipeline++;
	}
	return (true);
}

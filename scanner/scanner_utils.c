/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:41:00 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:41:01 by iabkadri         ###   ########.fr       */
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
	return (c == '|' || c == '<' || c == '>');
}

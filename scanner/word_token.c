/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:41:12 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:41:13 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tokentype	getword_token(char **pipeline, char **lexeme)
{
	char	*ptr;

	*lexeme = NULL;
	ptr = *pipeline;
	while (is_not_end_of_sequence(*ptr))
	{
		*lexeme = get_sequence(&ptr, lexeme);
		if (*lexeme == NULL)
			return (NIL);
	}
	*pipeline = ptr;
	return (WORD);
}

int	is_not_end_of_sequence(char c)
{
	return (!ft_isspace(c) && !isopt(c) && c != '\0');
}

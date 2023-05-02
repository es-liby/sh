/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:31:39 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/02 12:40:12 by iabkadri         ###   ########.fr       */
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
	return (!ft_isspace(c) && !ispipe_opt(c) && !isredir_opt(c)
		&& c != '\0');
}

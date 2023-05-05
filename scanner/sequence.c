/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:41:06 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:41:07 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*join_quoted_word(char **ptr, char **lexeme);
static char	*join_word(char **ptr, char **lexeme);
static char	*ft_getword(char **ptr);
static int	is_not_end_of_word(char c);

char	*get_sequence(char **ptr, char **lexeme)
{
	if (**ptr == '\'' || **ptr == '"')
	{
		*lexeme = join_quoted_word(ptr, lexeme);
		if (*lexeme == NULL)
			return (NULL);
	}
	else
		*lexeme = join_word(ptr, lexeme);
	return (*lexeme);
}

static char	*join_word(char **ptr, char **lexeme)
{
	char	*word;

	word = ft_getword(ptr);
	if (word == NULL)
		return (NULL);
	*lexeme = ft_strjoin(*lexeme, word);
	free(word);
	return (*lexeme);
}

static char	*join_quoted_word(char **ptr, char **lexeme)
{
	char	*qword;

	qword = quote(ptr, **ptr);
	if (qword == NULL)
		return (free(*lexeme), NULL);
	*lexeme = ft_strjoin(*lexeme, qword);
	free(qword);
	return (*lexeme);
}

static char	*ft_getword(char **ptr)
{
	char	*word;
	size_t	len;

	len = 0;
	while (is_not_end_of_word((*ptr)[len]))
		len++;
	word = ft_substr(*ptr, 0, len);
	*ptr += len;
	return (word);
}

static int	is_not_end_of_word(char c)
{
	return (is_not_end_of_sequence(c) && c != '\'' && c != '"');
}

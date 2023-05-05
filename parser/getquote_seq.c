/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getquote_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:39:09 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:39:10 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*join_value_with_word(char *value, char *word);
static char	*get_subword(char **ptr);

char	*get_the_quoted_sequence(char **ptr)
{
	char	*quoted_seq;
	char	*word;
	char	*value;

	quoted_seq = NULL;
	word = NULL;
	value = NULL;
	if (**ptr == '$')
		value = find_variable_and_get_value(ptr);
	word = get_subword(ptr);
	if (word == NULL)
		return (free(value), NULL);
	quoted_seq = join_value_with_word(value, word);
	return (quoted_seq);
}

static char	*join_value_with_word(char *value, char *word)
{
	char	*join;
	char	*value_dup;

	if (word == NULL)
	{
		value_dup = ft_strdup(value);
		return (free(value), value_dup);
	}
	join = ft_strjoin(value, word);
	free(word);
	return (join);
}

static char	*get_subword(char **ptr)
{
	char	*word;
	size_t	len;

	len = 0;
	while ((*ptr)[len] && (*ptr)[len] != '"' && (*ptr)[len] != '$')
		len++;
	word = ft_substr(*ptr, 0, len);
	*ptr += len;
	return (word);
}

char	*advance_ptr_and_return_nil_dup(char **ptr)
{
	++*ptr;
	return (ft_strdup("\0"));
}

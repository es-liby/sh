/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:01:47 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/11 22:52:45 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*join_value_with_word(char *value, char *word);
static void	set_seq_word_value_to_null(char **seq, char **word, char **value);

char	*get_sequence_inside_squote(char **ptr)
{
	char	*word;
	int		len;

	++*ptr;	//	skipe the ' character
	len = 0;
	while ((*ptr)[len] && (*ptr)[len] != '\'')
		len++;
	if (len == -1)
		return (NULL);
	word = ft_substr(*ptr, 0, len);
	if ((*ptr)[len] == '\'')
		len++;
	*ptr += len;
	return (word);
}

char	*get_sequence_inside_dquote(char **ptr)
{
	char	*seq;
	char	*word;
	char	*value;
	char	*join;

	++*ptr;	//	skip double quotes
	set_seq_word_value_to_null(&seq, &word, &value);
	while (**ptr != '"')
	{
		if (**ptr == '$')
			value = find_variable_and_get_value(ptr);
		word = get_word(ptr);
		if (word == NULL)
			return (free(value), free(seq), NULL);
		join = join_value_with_word(value, word);
		seq = ft_strjoin(seq, join);
		free(join);
	}
	++*ptr;	//	skip double quotes
	return (seq);
}

char	*get_word( char **ptr)
{
	char	*word;
	size_t	len;

	len = 0;
	while (is_word_char((*ptr)[len]))
		len++;
	word = ft_substr(*ptr, 0, len);
	*ptr += len;
	return (word);
}

static char	*join_value_with_word(char *value, char *word)
{
	char	*join;

	if (word == NULL)
		return (value);
	join = ft_strjoin(value, word);
	free(word);
	return (join);
}

static void	set_seq_word_value_to_null(char **seq, char **word, char **value)
{
	*seq = NULL;
	*word = NULL;
	*value = NULL;
}

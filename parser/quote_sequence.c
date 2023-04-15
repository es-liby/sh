/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:01:47 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/15 18:23:30 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_sequence_inside_squote(char **ptr)
{
	char	*word;
	int		len;

	++*ptr;	//	skip the ' character
	len = 0;
	while ((*ptr)[len] && (*ptr)[len] != '\'')
		len++;
	word = ft_substr(*ptr, 0, len);
	if ((*ptr)[len] == '\'')
		len++;	//	skip the ' character
	*ptr += len;
	return (word);
}

char	*get_sequence_inside_dquote(char **ptr)
{
	char	*tmp_ptr;
	char	*quoted_seq;

	++*ptr;	//	skip double quotes
	if (**ptr == '"')
		return (advance_ptr_and_return_nil_dup(ptr));
	quoted_seq = NULL;
	while (**ptr != '"')
	{
		tmp_ptr = get_the_quoted_sequence(ptr);
		quoted_seq = ft_strjoin(quoted_seq, tmp_ptr);
		free(tmp_ptr);
	}
	++*ptr;	//	skip double quotes
	return (quoted_seq);
}

char	*get_word(char **ptr)
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

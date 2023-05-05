/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:39:01 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:39:02 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	expand(t_list *token);

int	perform_expand(t_list *tokens)
{
	while (tokens)
	{
		if (tokens->type == WORD)
			expand(tokens);
		if (p_match(&tokens, HEREDOC))
		{
			if (p_match(&tokens, WORD))
				continue ;
		}
		advance(&tokens);
	}
	return (true);
}

static void	expand(t_list *token)
{
	char	*ptr;
	char	*new_lexeme;
	char	*sub_seq;

	new_lexeme = NULL;
	ptr = (char *)token->lexeme;
	while (*ptr)
	{
		sub_seq = get_sub_sequence(&ptr);
		if (sub_seq == NULL)
			continue ;
		new_lexeme = ft_strjoin(new_lexeme, sub_seq);
		free(sub_seq);
	}
	free(token->lexeme);
	token->lexeme = new_lexeme;
}

char	*get_sub_sequence(char **ptr)
{
	char	*sub_seq;

	if (**ptr == '\'')
		sub_seq = get_sequence_inside_squote(ptr);
	else if (**ptr == '"')
		sub_seq = get_sequence_inside_dquote(ptr);
	else if (**ptr == '$')
		sub_seq = find_variable_and_get_value(ptr);
	else
		sub_seq = get_word(ptr);
	return (sub_seq);
}

bool	is_word_char(char c)
{
	return (c != '\0' && c != '$' && c != '\'' && c != '"');
}

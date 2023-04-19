/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:28:59 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 18:01:46 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parser(t_list **tokens, t_pipeline **plist)
{
	t_list		*tmp_ptr_tokens;

	tmp_ptr_tokens = *tokens;
	*plist = NULL;
	if (perform_expand(tmp_ptr_tokens) == EOF)
		return (EOF);
	if (perform_redirections_and_set_cmds(plist, &tmp_ptr_tokens) == EOF)
		return (EOF);
	if (search_and_set_path_for_cmds(*plist) == EOF)
		return (EOF);
	return (true);
}

int	p_match(t_list **tokens, t_tokentype type)
{
	if (*tokens == NULL)
		return (false);
	if ((*tokens)->type != type)
		return (false);
	advance(tokens);
	return (true);
}

void	advance(t_list **tokens)
{
	if (*tokens != NULL)
		*tokens = (*tokens)->next;
}

t_tokentype	peek_type(t_list *token)
{
	if (token == NULL)
		return (NIL);
	return (token->type);
}

t_tokentype	peek_previous_type(t_list *token)
{
	if (token == NULL || token->prev == NULL)
		return (NIL);
	return (token->prev->type);
}

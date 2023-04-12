/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:28:59 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/11 23:38:12 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parser(t_list **tokens, t_pipeline **plist)
{
	t_list	*tmp_ptr;

	tmp_ptr = *tokens;
	(void)plist;
	perform_expand(tmp_ptr);
	if (perform_redirections(&tmp_ptr) == EOF)
		return ;
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

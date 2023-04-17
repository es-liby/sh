/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:34:46 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/15 14:26:18by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	pipeline_is_invalid(t_list *token);

bool	complete_pipeline(t_list **tokens)
{
	t_list	*new_tokens_list;
	char	*pipeline;

	if (pipeline_is_invalid((*tokens)->next))
		return (syn_err((*tokens)->next), false);
	pipeline = readline("> ");
	if (pipeline == NULL)
		exit(EXIT_FAILURE);
	scanner(&new_tokens_list, pipeline);
	free(pipeline);
	ft_lstadd_back(tokens, new_tokens_list);
	return (true);
}

bool	pipeline_not_completed(t_list *token)
{
	if (peek_type(token) != WORD && !is_redir_token(token))
		return (true);
	return (false);
}

static bool	pipeline_is_invalid(t_list *token)
{
	if (peek_type(token) == NIL)
		return (false);
	return (true);
}

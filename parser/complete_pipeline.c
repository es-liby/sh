/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:15:11 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 18:15:12 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	pipeline_is_invalid(t_list *token);
static void	delete_pipe_token(t_list **pipe_token);

bool	complete_pipeline(t_list **tokens)
{
	t_list	*new_tokens_list;
	char	*pipeline;
	t_list	*pipe_token;

	if (pipeline_is_invalid((*tokens)->next->next))
		return (syn_err((*tokens)->next), false);
	pipe_token = (*tokens)->next;
	(*tokens)->next = (*tokens)->next->next;
	delete_pipe_token(&pipe_token);
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

static void	delete_pipe_token(t_list **pipe_token)
{
	free((*pipe_token)->lexeme);
	free(*pipe_token);
}

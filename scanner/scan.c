/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:40:54 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:40:55 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_tokentype	get_next_token(char **pipeline, char **lexeme);
static t_tokentype	tokenfunc(t_tokentype type, char **pipeline, char **lexeme);
static t_tokentype	gettype_of_token(char c);

int	scan(t_list **tokens, char *pipeline)
{
	char		*lexeme;
	t_tokentype	type;

	if (*pipeline == '\0')
		return (NIL);
	*tokens = NULL;
	type = get_next_token(&pipeline, &lexeme);
	while (type != END && type != NIL)
	{
		addtoken(tokens, lexeme, type);
		type = get_next_token(&pipeline, &lexeme);
	}
	if (type == NIL)
		return (ft_lstclear(tokens, free), NIL);
	return (type);
}

static t_tokentype	get_next_token(char **pipeline, char **lexeme)
{
	t_tokentype	type;

	if (**pipeline == '\0')
		return (END);
	while (**pipeline && ft_isblank(**pipeline) && !isopt(**pipeline))
		++*pipeline;
	type = gettype_of_token(**pipeline);
	if (type == END)
		return (END);
	return (tokenfunc(type, pipeline, lexeme));
}

static t_tokentype	tokenfunc(t_tokentype type, char **pipeline, char **lexeme)
{
	if (type == REDIR)
		return (getredir_token(pipeline, lexeme));
	if (type == PIPE)
		return (getpipe_token(pipeline, lexeme));
	return (getword_token(pipeline, lexeme));
}

static t_tokentype	gettype_of_token(char c)
{
	if (c == '\0')
		return (END);
	if (isredir_opt(c))
		return (REDIR);
	if (ispipe_opt(c))
		return (PIPE);
	return (WORD);
}

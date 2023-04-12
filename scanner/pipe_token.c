/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:22:15 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/07 15:23:28 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tokentype	getpipe_token(char **pipeline, char **lexeme)
{
	++*pipeline;	//	skip the '|' character
	*lexeme = ft_strdup("|");
	return (PIPE);
}

int	ispipe_opt(char c)
{
	return (c == '|');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:13:55 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/02 18:33:22 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYMBOLS_H
# define SYMBOLS_H

typedef enum e_tokentype
{
	REDIR = 0,
	PIPE,
	WORD,
	REDIR_IN,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	HEREDOC,
	END,
	NIL
}	t_tokentype;

typedef enum e_builtin
{
	ECHO = 0,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NONE
}	t_builtin;

#endif
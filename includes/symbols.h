/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:41:40 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:41:41 by iabkadri         ###   ########.fr       */
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
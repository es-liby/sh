/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:13:55 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 18:13:56 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYMBOLS_H
# define SYMBOLS_H

typedef enum e_tokentype
{
	REDIR,
	PIPE,
	WORD,
	REDIR_IN,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	HEREDOC,
	ENVVAR,
	END,
	NIL
}	t_tokentype;

#endif
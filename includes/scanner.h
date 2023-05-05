/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:41:32 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:41:33 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include <symbols.h>
# include <libft.h>

/*	scanner.c	*/
int			scan(t_list **tokens, char *cmdline);

/*	redir_token.c	*/
t_tokentype	getredir_token(char **pipeline, char **token);
int			isredir_opt(char c);

/*	pipe_token.c	*/
t_tokentype	getpipe_token(char **pipeline, char **token);
int			ispipe_opt(char c);

/*	quote_token.c	*/
char		*del_quotes(char *ptr, char c);
size_t		get_subword_len(const char *ptr, char c);
int			is_not_surronded_by_quotes(char *tmp_ptr, char c);
int			isquote_opt(char c);

/*	quote.c	*/
char		*quote(char **ptr, char c);

/*	word_token.c	*/
t_tokentype	getword_token(char **pipeline, char **token);
int			is_not_end_of_sequence(char c);

/*	sequence.c	*/
char		*get_sequence(char **ptr, char **lexeme);

/*	scanner_utils.c	*/
void		addtoken(t_list **tokens, char *token, t_tokentype type);
int			s_match(char **ptr, char c);
int			isopt(char c);

#endif
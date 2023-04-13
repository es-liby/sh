/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 01:54:35 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/12 01:23:26 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <symbols.h>
# include <libft.h>
# include <structs.h>

/*	parser.c	*/
void		parser(t_list **tokens, t_pipeline **plist);
int			p_match(t_list **tokens, t_tokentype type);
void		advance(t_list **tokens);
t_tokentype	peek_type(t_list *token);
t_tokentype	peek_previous_type(t_list *token);

/*	expand.c	*/
void		perform_expand(t_list *tokens);
char		*get_sub_sequence(char **ptr);
int			is_word_char(char c);

/*	quote_sequence.c	*/
char		*get_sequence_inside_squote(char **ptr);
char		*get_sequence_inside_dquote(char **ptr);
char		*get_word( char **ptr);

/*	redirections.c	*/
int			perform_redirections(t_pipeline **plist, t_list **tokens);
void		print_syntax_error(t_list *tokens);

/*	set.c	*/
int			set_cmd_and_args(t_pipeline **plist, t_list **tokens, t_fds *fds,
		int i);
int	set_input_and_output_streams(t_pipeline **plist, t_list **tokens,
		t_fds *fds, int i);
void		set_pipe(t_pipeline **plist, t_fds *fds, int i);

/*	pipe_fds.c	*/
t_fds		*count_and_open_pipes(t_list *tokens);
void		close_pipes(int **fds, int n);
void		clear_pipes(t_fds *fds);

/*	redir.c	*/
int			perform_redir_input(t_list **tokens);
int			perform_redir_output(t_list **tokens, t_tokentype type);
int			is_redir_token(t_list *token);

int			set_cmd_and_args(t_pipeline **plist, t_list **tokens, t_fds *fds,
			int i);

/*	heredoc.c	*/
int			redir_heredoc(t_pipeline **plist, t_list **tokens);

#endif

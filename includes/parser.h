/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 01:54:35 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/15 14:35:37 by iabkadri         ###   ########.fr       */
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

/*	plist_utils.c	*/
t_pipeline	*last_plist(t_pipeline *plist);
void		addback(t_pipeline **plist, t_pipeline *new);

/*	pipeline.c	*/
bool		complete_pipeline(t_list **tokens);
bool		pipeline_not_completed(t_list *token);

/*	expand.c	*/
int			perform_expand(t_list *tokens);
char		*get_sub_sequence(char **ptr);
bool		is_word_char(char c);

/*	quote_sequence.c	*/
char		*get_sequence_inside_squote(char **ptr);
char		*get_sequence_inside_dquote(char **ptr);
char		*get_word(char **ptr);

/*	getquote_seq.c	*/
char		*get_the_quoted_sequence(char **ptr);
char		*advance_ptr_and_return_nil_dup(char **ptr);

/*	set_memebers.c	*/
int			perform_redirections_and_set_cmds(t_pipeline **plist,
		t_list **tokens);
t_pipeline	*new_plist(void);
void		print_syntax_error(t_list *tokens);

/*	set.c	*/
int			set_cmd_and_args(t_pipeline **plist, t_list **tokens, t_fds *fds,
		int i);
int	set_input_and_output_streams(t_pipeline **plist, t_list **tokens,
		t_fds *fds, int i);

/*	io_streams.c	*/
int			set_input_and_output_streams(t_pipeline **plist, t_list **tokens,
			t_fds *fds, int i);

/*	pipe_fds.c	*/
t_fds		*count_and_open_pipes(t_list *tokens);
void		close_pipes(t_fds *fds);
void		clear_pipes(t_fds *fds);

/*	redir.c	*/
int			perform_redir_input(t_pipeline **plist, t_list **tokens, t_fds *fds, int i);
int			perform_redir_output(t_pipeline **plist, t_list **tokens, t_fds *fds, int i);
int			is_redir_token(t_list *token);

int			set_cmd_and_args(t_pipeline **plist, t_list **tokens, t_fds *fds,
			int i);

/*	heredoc.c	*/
int			redir_heredoc(t_pipeline **plist, t_list **tokens, t_fds *fds,
			int i);

#endif

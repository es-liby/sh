/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 01:54:35 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/18 11:57:37 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <symbols.h>
# include <libft.h>
# include <structs.h>

/*	parser.c	*/
int			parser(t_list **tokens, t_pipeline **plist);
int			p_match(t_list **tokens, t_tokentype type);
void		advance(t_list **tokens);
t_tokentype	peek_type(t_list *token);
t_tokentype	peek_previous_type(t_list *token);

/*	plist_utils.c	*/
t_pipeline	*new_plist(void);
t_pipeline	*last_plist(t_pipeline *plist);
void		addback(t_pipeline **plist, t_pipeline *new);

/*	complete_pipeline.c	*/
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

/*	cmd_and_args.c	*/
int			set_cmd_and_args(t_pipeline **plist, t_list **tokens);
int			set_input_and_output_streams(t_pipeline **plist, t_list **tokens);

/*	split_args.c	*/
char	**split_args(char *args);

/*	io_streams.c	*/
int			set_input_and_output_streams(t_pipeline **plist, t_list **tokens);

/*	pipe_fds.c	*/
t_fds		*count_and_open_pipes(t_list *tokens);
void		open_pipes(int **fds, int n);
void		close_pipes(void);
void		clear_pipes(void);

/*	perform_redir_io.c	*/
int			perform_redir_input(t_pipeline **plist, t_list **tokens);
int			perform_redir_output(t_pipeline **plist, t_list **tokens);
int			is_redir_token(t_list *token);

int			set_cmd_and_args(t_pipeline **plist, t_list **tokens);

/*	heredoc.c	*/
int			redir_heredoc(t_pipeline **plist, t_list **tokens);

/*	heredoc_utils.c	*/
char		*get_sub_sequence_of_heredoc(char **line);
void		writeline_to_heredoc_file_without_expanding(char *line, int fd);
void		writeline_to_heredoc_file_with_expanding(char *line, int fd);

/*	readlines_heredoc.c	*/
int			read_and_write_line_to_heredoc_file(t_list *tokens, int fd,
				int expanded);

/*	../utils/heredoc_signals.c	*/
void		handle_signals_for_heredoc(void);

/*	print.c	*/
void		syn_err(t_list *tokens);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 07:29:22 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/24 12:00:55 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <libft.h>
# include <ft_fprintf.h>
# include <structs.h>

# define JOIN 2
# define ADD 1

/*	exec.c	*/
int			execute(t_pipeline *plist);
void		update_exit_status(int status);

/*	search_path.c	*/
int			search_and_set_path_for_cmds(t_pipeline *plist);

/*	builtins.c	*/
int			cdcmd(char **args);
int			pwdcmd(char **args);
int			echocmd(char **args);
int			envcmd(char **args);
int			exitcmd(char **args);
int			exportcmd(char **args);
int			set_value_of_new_envvar(char *new_envvar, char **value, size_t len);
void		join_new_envvar(char *key, char *value);
void		add_new_envvar(char *new_envvar, char *key, char *value);
int			unsetcmd(char **args);

/*	exec_builtin.c	*/
void		execute_builtin_cmd(t_pipeline *plist, t_builtin cmdtype);
t_builtin	is_a_builtin_cmd(char *cmd);

/*	streams.c	*/
void		dup_streams(t_pipeline *plist, int *stdin_dup, int *stdout_dup);
void		getback_io_streams(t_pipeline *plist, int stdin_dup,
				int stdout_dup);
int			close_streams(t_pipeline *plist);

/*	ids.c	*/
void		add_id(t_ids **ids, pid_t pid);
void		wait_pids_and_update_exit_status(t_ids **ids);

#endif

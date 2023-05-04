/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 07:29:22 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 21:24:27 by iabkadri         ###   ########.fr       */
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
void		execute(t_pipeline *plist);
void		update_exit_status(int status);

/*	builtins.c	*/
void		cdcmd(char **args);
void		pwdcmd(char **args);
void		update_cwd(char *arg);
void		update_pwd_and_oldpwd(char *cwd);
void		echocmd(char **args);
void		envcmd(char **args);
void		exitcmd(char **args);
void		exportcmd(char **args);
int			set_value_of_new_envvar(char *new_envvar, char **value, size_t len);
void		join_new_envvar(char *key, char *value);
void		add_new_envvar(char *key, char *value);
void		unsetcmd(char **args);

/*	streams.c	*/
int			duplicate_io_streams(t_pipeline *plist);
int			dup_streams(t_pipeline *plist, int *stdin_dup, int *stdout_dup);
void		getback_io_streams(t_pipeline *plist, int stdin_dup,
				int stdout_dup);
int			close_streams(t_pipeline *plist);
int			ft_dup(int fd);

/*	split_plist.c	*/
void		split_plist(t_pipeline *plist);
size_t		getsp_size(char **args);

/*	check_cmds.c	*/
int			check_if_valid(t_pipeline *plist);
char		**check_cmd_path(char *cmd);

/*	execute_builtins.c	*/
int			execute_builtin(t_pipeline **plist);
bool		check_if_builtin(char *cmd);
bool		if_builtin_execute(t_pipeline **plist);

/*	split_args.c	*/
char		**split_args(char **args);

/*	ids.c	*/
void		add_id(t_ids **ids, pid_t pid);
void		wait_pids_and_update_exit_status(t_ids **ids);

#endif
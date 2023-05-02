/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 07:29:22 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/02 12:27:48 by iabkadri         ###   ########.fr       */
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
int			cdcmd(char **args);
int			pwdcmd(char **args);
void		update_cwd(char *arg);
void		update_pwd_and_oldpwd(char *cwd);
int			echocmd(char **args);
int			envcmd(char **args);
int			exitcmd(char **args);
int			exportcmd(char **args);
int			set_value_of_new_envvar(char *new_envvar, char **value, size_t len);
void		join_new_envvar(char *key, char *value);
void		add_new_envvar(char *key, char *value);
int			unsetcmd(char **args);

/*	streams.c	*/
int			duplicate_io_streams(t_pipeline *plist);
int			dup_streams(t_pipeline *plist, int *stdin_dup, int *stdout_dup);
void		getback_io_streams(t_pipeline *plist, int stdin_dup,
				int stdout_dup);
int			close_streams(t_pipeline *plist);

/*	split_plist.c	*/
void		split_plist(t_pipeline *plist);
size_t		getsp_size(char **args);

/*	check_cmds.c	*/
int			check_if_valid(t_pipeline *plist, char **paths);
char		**check_cmd_path(char *cmd);
int			check_if_build_in(t_pipeline **plist);

/*	split_args.c	*/
char		**split_args(char **args);

/*	ids.c	*/
void		add_id(t_ids **ids, pid_t pid);
void		wait_pids_and_update_exit_status(t_ids **ids);

#endif
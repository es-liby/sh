#ifndef EXECUTE_H
# define EXECUTE_H

# include <libft.h>
# include <ft_fprintf.h>
# include <structs.h>

/*	exec.c	*/
int		execute(t_pipeline *plist);
char	**get_envlist(void);

/*	search_path.c	*/
int		search_and_set_path_for_cmds(t_pipeline *plist);

/*	ids.c	*/
void	addid(t_ids *ids, int pid);
void	wait_ids(t_ids *ids);

#endif

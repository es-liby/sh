#include <minishell.h>

static t_ids	*last_id(t_ids *ids);

void	addid(t_ids *ids, int pid)
{
	if (ids == NULL)
	{
		ids = ft_calloc(1, sizeof(t_ids));
		ids->id = pid;
		ids->next = NULL;
		return ;
	}
	addid(last_id(ids)->next, pid);
}

static t_ids	*last_id(t_ids *ids)
{
	while (ids && ids->next)
		ids = ids->next;
	return (ids);
}

void	wait_ids(t_ids *ids)
{
	int	status;

	while (ids)
	{
		waitpid(ids->id, &status, 0);
		ids = ids->next;
	}
	g_gbl.exit_status = status;
}

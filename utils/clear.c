#include <minishell.h>

void	clear(t_pipeline **plist)
{
	t_pipeline	*tmp;

	while (*plist)
	{
		tmp = *plist;
		*plist = (*plist)->next;
		free(tmp->cmd);
		free(tmp->args);
	}
}

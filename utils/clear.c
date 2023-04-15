#include <minishell.h>

void	clear_plist(t_pipeline **plist)
{
	t_pipeline	*tmp;

	while (*plist)
	{
		tmp = *plist;
		*plist = (*plist)->next;
		free(tmp->cmd);
		free(tmp->args);
		free(tmp);
	}
}

void	remove_and_clear_heredoc_files(void)
{
	t_list	*tmp_ptr;

	tmp_ptr = g_gbl.heredoc_files;
	while (tmp_ptr)
	{
		if (unlink(tmp_ptr->content) == -1)
			exit(EXIT_FAILURE);
		advance(&tmp_ptr);
	}
	ft_lstclear(&g_gbl.heredoc_files, free);
}

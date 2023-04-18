/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd_unset_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:41:17 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/04/18 09:29:46 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	freestr(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

void	ft_pwd(void)
{
	char	buff[500];

	if (!getcwd((buff), sizeof(buff)))
	{
		write(1, "Eroor\n", 6);
		return ;
	}
	else
		ft_putstr(buff);
}

void	ft_cd(char *path)
{
	if (chdir(path) == 0)
		return ;
	else
	{
		write(1, "cd: not a directory: ", 21);
		ft_putstr(path);
		write(1, "\n", 1);
	}
}

int	ft_unset(t_env **e, char *str)
{
	t_env	*tmp;

	if (!(*e) || !str)
		return (0);
	tmp = *e;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, str))
		{
			tmp->key = NULL;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_exit(void)
{
	printf("exit\n");
	_Exit(0);
}

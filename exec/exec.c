/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 10:19:38 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/04/18 10:39:48 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	f()
{
	system("leaks minishell");
}

int main(int ac, char **av, char **env)
{
	atexit(f);
	t_env *e;

	if (!ft_export(e, env, av))
	{
		write(1, "eroor\n", 6);
		exit(1);
	}
	// ft_cd(av[1]);
	// ft_env(env);
	// ft_pwd();
	//ft_echo(av);  //./minishell echo "type here ..."
	return (0);
}

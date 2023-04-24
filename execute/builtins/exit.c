/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:00:39 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/24 12:00:40 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	exit_with_status_number(char *st_number);
static void	exit_with_last_status_number(void);
static bool	is_not_valid_status_number(char *st_number);

int	exitcmd(char **args)
{
	if (args[0] != NULL && args[1] != NULL)
	{
		ft_fprintf(2, "exit\nbash: exit: too many arguments\n");
		return (EOF);
	}
	if (args[0] != NULL)
	{
		if (is_not_valid_status_number(args[0]))
			return (EOF);
		exit_with_status_number(args[0]);
	}
	else
		exit_with_last_status_number();
	return (true);
}

static void	exit_with_status_number(char *st_number)
{
	int	status_number;

	status_number = ft_atoi(st_number);
	update_exit_status(status_number);
	exit(g_gbl.exit_status);
}

static void	exit_with_last_status_number(void)
{
	ft_fprintf(1, "exit\n");
	exit(g_gbl.exit_status);
}

static bool	is_not_valid_status_number(char *st_number)
{
	int	i;

	i = 0;
	while (st_number[i] && ft_isdigit(st_number[i]))
		i++;
	if (st_number[i] != '\0')
	{
		g_gbl.exit_status = 2;
		ft_fprintf(2, "exit\nbash: exit: %s: numeric argument required\n");
		return (true);
	}
	return (false);
}

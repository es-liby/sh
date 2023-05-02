/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:32:00 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/05/02 10:06:48 by iabkadri         ###   ########.fr       */
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
		ft_fprintf(2, "exit\nsh: exit: too many arguments\n");
		return (update_exit_status(1), EOF);
	}
	if (args[0] != NULL)
	{
		if (is_not_valid_status_number(args[0]))
			exit(g_glob.exit_status);
		exit_with_status_number(args[0]);
	}
	else
		exit_with_last_status_number();
	update_exit_status(0);
	return (true);
}

static void	exit_with_status_number(char *st_number)
{
	long status_number;

	status_number = ft_atoi(st_number);
	if (status_number == -1 && ft_strlen(st_number) > 2)
	{
		ft_fprintf(2, "exit\n");
		ft_fprintf(2, "sh: exit: %s: numeric argument required\n", st_number);
		g_glob.exit_status = 255;
	}
	else
	{
		g_glob.exit_status = (unsigned char)status_number;
		ft_fprintf(1, "exit\n");
	}
	exit(status_number);
}

static void	exit_with_last_status_number(void)
{
	ft_fprintf(1, "exit\n");
	exit(g_glob.exit_status);
}

static bool	is_not_valid_status_number(char *st_number)
{
	int	i;

	i = 0;
	if (st_number[i] == '-' || st_number[i] == '+')
		i++;
	while (st_number[i] && ft_isdigit(st_number[i]))
		i++;
	if (st_number[i] != '\0')
	{
		ft_fprintf(2, "exit\n");
		ft_fprintf(2, "sh: exit: %s: numeric argument required\n", st_number);
		return (update_exit_status(255), true);
	}
	return (false);
}

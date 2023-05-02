/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:00:24 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/24 14:13:12 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_args_with_newline_at_end(char **args);
static void	print_args_without_newline_at_end(char **args);
static bool	there_is_n_option(char *arg);

int	echocmd(char **args)
{
	int	i;

	i = -1;
	if (there_is_n_option(args[++i]) == true)
	{
		while (there_is_n_option(args[++i]))
			;
		print_args_without_newline_at_end(args + i);
	}
	else
		print_args_with_newline_at_end(args);
	update_exit_status(0);
	return (true);
}

static void	print_args_with_newline_at_end(char **args)
{
	int	indx;

	indx = -1;
	while (args[++indx])
	{
		ft_fprintf(1, "%s", args[indx]);
		if (args[indx + 1] != NULL)
			ft_fprintf(1, " ");
	}
	ft_fprintf(1, "\n");
}

static void	print_args_without_newline_at_end(char **args)
{
	int	indx;

	indx = -1;
	while (args[++indx])
	{
		ft_fprintf(1, "%s", args[indx]);
		if (args[indx + 1] != NULL)
			ft_fprintf(1, " ");
	}
}

static bool	there_is_n_option(char *arg)
{
	int	indx;

	if (arg == NULL)
		return (false);
	if (arg[0] == '-' && arg[1] == 'n')
	{
		indx = 2;
		if (arg[indx] == '\0')
			return (true);
		while (arg[indx] && arg[indx] == 'n')
			indx++;
		if (arg[indx] != '\0')
			return (false);
		return (true);
	}
	return (false);
}

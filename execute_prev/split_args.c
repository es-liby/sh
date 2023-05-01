/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:34:28 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/01 16:11:23 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		set_arg(char **arg_ptr, char *arg, size_t *i);
static size_t	getargs_size(char **args);
static size_t	getargs_size(char **args);

char	**split_args(char **args)
{
	char	**args_ptr;
	size_t	size;
	size_t	i;
	size_t	j;

	size = getargs_size(args);
	args_ptr = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	j = -1;
	while (i < size)
		set_arg(args_ptr, args[++j], &i);
	args_ptr[i] = NULL;
	return (args_ptr);
}

static void	set_arg(char **arg_ptr, char *arg, size_t *i)
{
	char	**tab_ptr;
	int		j;

	tab_ptr = ft_split(arg, ' ');
	j = -1;
	while (tab_ptr[++j])
	{
		arg_ptr[*i] = ft_strdup(tab_ptr[j]);
		++*i;
	}
	free_tab(tab_ptr);
}

static size_t	getargs_size(char **args)
{
	char	**tab_ptr;
	size_t	size;
	int		i;

	size = 0;
	i = -1;
	while (args[++i])
	{
		tab_ptr = ft_split(args[i], ' ');
		size += getsp_size(tab_ptr);
		free_tab(tab_ptr);
	}
	return (size);
}

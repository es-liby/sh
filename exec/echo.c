/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:55:39 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/04/17 14:29:05 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_echo(char **str)
{
	int		i;
	int		with_new_line;
	t_list	*head;

	head = NULL;
	i = 1;
	while (str[++i])
		ft_lstaddback(&head, ft_lstnew(str[i]));
	print_echo(head);
}

void	print_echo(t_list *head)
{
	t_list	*tmp;
	int		nl;

	nl = 1;
	if (!head)
		return ;
	tmp = head;
	while (check_flag_n(tmp) == 1)
	{
		nl = 0;
		tmp = tmp->next;
	}
	while (tmp)
	{
		ft_fprintf(1, "%s ", tmp->value);
		tmp = tmp->next;
	}
	if (nl == 1)
		write(1, "\n", 1);
}

int	check_flag_n(t_list *node)
{
	int	i;

	i = 2;
	if (node->value[0] == '-' && node->value[1] == 'n')
	{
		while (node->value[i])
		{
			if (node->value[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

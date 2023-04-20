/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 12:17:50 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/04/18 10:07:15 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_env(char **env)
{
	int		i;
	t_env	*e;
	t_env	*tmp;

	i = -1;
	e = NULL;
	while (env[++i])
		ft_lstaddback_env(&e, ft_lstnew_env(env[i]));
	print_env(e);
	while (e)
	{
		tmp = e;
		e = e->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

t_env	*other_checks(char *str)
{
	if (ft_strchr(str, '=') && str[ft_strlen(str) - 1] != '='
		&& more_than_equal(str) == 1)
		return (handle_simple_assignement(str));
	else if (ft_strchr(str, '=') && str[ft_strlen(str) - 1] == '=')
		return (handle_equal_at_the_end(str));
	else if (more_than_equal(str) >= 1 && !ft_strchr(str, '+'))
		return (handle_ls_colors_variable(str));
	else
		return (handle_the_rest(str));
}

t_env	*ft_lstnew_env(char *str)
{
	t_env	*e;
	char	**splited;

	if (ft_strchr(str, '+')
		&& (ft_strchr(str, '+') + 1)[0] == '=' && more_than_equal(str) != 1)
		return (handle_more_than_equal(str));
	else if (ft_strchr(str, '+')
		&& (ft_strchr(str, '+') + 1)[0] == '='
			&& str[ft_strlen(str) - 1] == '=')
		return (handle_plus_equal_and_equal_at_end(str));
	else if (ft_strchr(str, '+') && (ft_strchr(str, '+') + 1)[0] == '='
		&& str[ft_strlen(str) - 1] != '=')
		return (handle_plus_equal_and_equal_not_at_the_end(str));
	else if (ft_strchr(str, '=') && str[ft_strlen(str) - 1] != '='
		&& more_than_equal(str) == 1)
		return (handle_simple_assignement(str));
	else if (ft_strchr(str, '=') && str[ft_strlen(str) - 1] == '=')
		return (handle_equal_at_the_end(str));
	else if (more_than_equal(str) >= 1 && !ft_strchr(str, '+'))
		return (handle_ls_colors_variable(str));
	else
		return (handle_the_rest(str));
}

void	ft_lstaddback_env(t_env **e, t_env *new)
{
	t_env	*t;

	if (e && new)
	{
		if (!(*e))
			*e = new;
		else
		{
			t = *e;
			while (t->next)
				t = t->next;
			t->next = new;
		}
	}
}

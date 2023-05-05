/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:40:39 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:40:40 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*join_subptr_with_tmp(char *tmp, char *ptr, size_t len);

char	*del_quotes(char *ptr, char c)
{
	char	*tmp;
	size_t	len;

	tmp = NULL;
	while (*ptr)
	{
		if (*ptr == c)
			ptr++;
		len = get_subword_len(ptr, c);
		tmp = join_subptr_with_tmp(tmp, ptr, len);
		ptr += len;
	}
	return (tmp);
}

size_t	get_subword_len(const char *ptr, char c)
{
	size_t	len;

	len = 0;
	while (ptr[len] && ptr[len] != c)
		len++;
	return (len);
}

int	is_not_surronded_by_quotes(char *tmp, char c)
{
	int	nq;

	nq = 0;
	while (*tmp)
	{
		if (*tmp == c)
			nq++;
		tmp++;
	}
	return (nq % 2);
}

int	isquote_opt(char c)
{
	return (c == '\'' || c == '"');
}

static char	*join_subptr_with_tmp(char *tmp, char *ptr, size_t len)
{
	char	*sub;

	sub = ft_substr(ptr, 0, len);
	tmp = ft_strjoin(tmp, sub);
	free(sub);
	return (tmp);
}

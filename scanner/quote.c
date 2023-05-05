/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:40:43 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:40:44 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		get_sequence_length(char *tmp_ptr, char c);

char	*quote(char **ptr, char c)
{
	char	*lexeme;
	char	*tmp_ptr;
	int		len;

	tmp_ptr = *ptr;
	len = get_sequence_length(tmp_ptr, c);
	lexeme = NULL;
	if (tmp_ptr[len] == '\0')
	{
		ft_fprintf(2, "sh: syntax error\n");
		return (NULL);
	}
	lexeme = ft_substr(tmp_ptr, 0, len + 1);
	*ptr += (len + 1);
	return (lexeme);
}

static int	get_sequence_length(char *tmp_ptr, char c)
{
	size_t	len;

	len = 0;
	if (tmp_ptr[len] == c)
		len++;
	while (tmp_ptr[len] != '\0' && tmp_ptr[len] != c)
		len++;
	return (len);
}

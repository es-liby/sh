/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:40:57 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/10 02:29:13 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*join;
	size_t	size;

	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = ft_calloc(size, sizeof(char));
	ft_strlcpy(join, s1, size);
	ft_strlcat(join, s2, size);
	free(s1);
	return (join);
}

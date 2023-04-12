/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:21:50 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/10 02:29:56 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	size;

	size = ft_strlen(s1) + 1;
	p = ft_calloc(size, sizeof(char));
	ft_strlcpy(p, s1, size);
	return (p);
}

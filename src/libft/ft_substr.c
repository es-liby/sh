/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:31:32 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/10 02:30:47 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	size;
	size_t	slen;

	if (s == NULL)
		return (NULL);
	size = len + 1;
	slen = ft_strlen(s);
	if (slen < len)
		size = slen + 1;
	if (slen <= start)
		size = 1;
	substr = ft_calloc(size, sizeof(char));
	ft_strlcpy(substr, s + start, size);
	return (substr);
}

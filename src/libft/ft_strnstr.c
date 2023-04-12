/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:47:34 by iabkadri          #+#    #+#             */
/*   Updated: 2022/10/19 18:03:12 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nl;

	nl = ft_strlen(needle);
	if (haystack == NULL && len == 0)
		return (NULL);
	if (nl == 0)
		return ((char *)haystack);
	while (*haystack != '\0' && len > 0)
	{
		if (ft_strncmp(haystack, needle, nl) == 0 && len >= nl)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}

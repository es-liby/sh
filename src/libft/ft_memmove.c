/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:47:18 by iabkadri          #+#    #+#             */
/*   Updated: 2022/10/19 17:48:45 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*pd;
	const char	*ps;

	pd = dst;
	ps = src;
	if (pd == NULL && ps == NULL)
		return (NULL);
	if (pd > ps && pd < ps + len)
	{
		pd += len;
		ps += len;
		while (len-- > 0)
			*--pd = *--ps;
	}
	else
		while (len-- > 0)
			*pd++ = *ps++;
	return (dst);
}

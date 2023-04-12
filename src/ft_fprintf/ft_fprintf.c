/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:31:15 by iabkadri          #+#    #+#             */
/*   Updated: 2023/02/10 15:31:16 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_fprintf.h>

void	ft_fprintf(int fd, const char *format, ...)
{
	va_list	ap;

	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format != '%')
			ft_putchar(fd, *format);
		else
			ft_handle(fd, *++format, ap);
		format++;
	}
	va_end(ap);
}

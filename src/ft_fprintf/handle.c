/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:31:17 by iabkadri          #+#    #+#             */
/*   Updated: 2023/02/10 15:31:18 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_fprintf.h>

static void	ft_putinteger(int fd, char spc, int i_val);
static void	ft_putaddress(int fd, unsigned long address);
static void	ft_putbase(int fd, unsigned long nbr, char *base);

void	ft_handle(int fd, char spc, va_list ap)
{
	if (spc == 'c' || spc == 'd' || spc == 'i')
		ft_putinteger(fd, spc, va_arg(ap, int));
	else if (spc == 'u')
		ft_putnbr(fd, (unsigned int)va_arg(ap, int));
	else if (spc == 'p')
		ft_putaddress(fd, (unsigned long)va_arg(ap, void *));
	else if (spc == 'x')
		ft_putbase(fd, va_arg(ap, unsigned int), "0123456789abcdef");
	else if (spc == 'X')
		ft_putbase(fd, va_arg(ap, unsigned int), "0123456789ABCDEF");
	else if (spc == 's')
		ft_putstr(fd, va_arg(ap, char *));
	else
		ft_putchar(fd, spc);
}

static void	ft_putinteger(int fd, char spc, int i_val)
{
	if (spc == 'c')
		ft_putchar(fd, i_val);
	else
		ft_putnbr(fd, i_val);
}

static void	ft_putaddress(int fd, unsigned long address)
{
	ft_putstr(fd, "0x");
	ft_putbase(fd, address, "0123456789abcdef");
}

static void	ft_putbase(int fd, unsigned long nbr, char *base)
{
	if (nbr >= 16)
		ft_putbase(fd, nbr / 16, base);
	ft_putchar(fd, base[nbr % 16]);
}

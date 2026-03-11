/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:19:24 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/11 17:07:54 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	handle_char_or_ints(int c, char *format, int *count)
{
	if (*format == 'c')
		*count += write(1, &c, 1);
	else
	{
		if (c == -2147483648)
		{
			ft_putnbr_fd(c, 1);
			*count += 11;
			return ;
		}
		if (c < 0 && c)
		{
			*count += write(1, "-", 1);
			c = -c;
		}
		ft_putnbr_fd(c, 1);
		*count += ft_numlen_base(c, 10);
	}
}

void	handle_string(char *str, int *count)
{
	int	len;

	len = 0;
	if (str == NULL)
		*count += write(1, "(null)", 6);
	else
	{
		len = ft_strlen(str);
		*count += write(1, str, len);
	}
}

void	handle_pointer(void *ptr, int *count)
{
	unsigned long	addr;

	if (!ptr)
	{
		*count += write(1, "(nil)", 5);
		return ;
	}
	addr = (unsigned long)ptr;
	*count += write(1, "0x", 2);
	ft_putnbr_base(addr, "0123456789abcdef");
	*count += ft_numlen_base(addr, 16);
}

void	handle_unsigned(unsigned int u, char *format, int *count)
{
	if (*format == 'u')
	{
		ft_putnbr_u_fd(u, 1);
		*count += ft_numlen_base(u, 10);
	}
	else if (*format == 'x')
	{
		ft_putnbr_base(u, "0123456789abcdef");
		*count += ft_numlen_base(u, 16);
	}
	else if (*format == 'X')
	{
		ft_putnbr_base(u, "0123456789ABCDEF");
		*count += ft_numlen_base(u, 16);
	}
}

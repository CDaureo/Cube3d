/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:32:37 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/11 17:08:56 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	selector(char *format, int *count, va_list args)
{
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'c' || *format == 'd' || *format == 'i')
				handle_char_or_ints(va_arg(args, int), format, count);
			else if (*format == 's')
				handle_string(va_arg(args, char *), count);
			else if (*format == 'p')
				handle_pointer(va_arg(args, void *), count);
			else if (*format == 'u' || *format == 'x' || *format == 'X')
				handle_unsigned(va_arg(args, unsigned int), format, count);
			else if (*format == '%')
				*count += write(1, "%", 1);
		}
		else
			*count += write(1, format, 1);
		format++;
	}
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start (args, format);
	selector((char *)format, &count, args);
	va_end(args);
	return (count);
}

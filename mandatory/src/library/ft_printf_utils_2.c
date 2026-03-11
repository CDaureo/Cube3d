/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:37:35 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/11 17:07:57 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_putnbr_u_fd(unsigned int n, int fd)
{
	char	c;

	if (n >= 10)
		ft_putnbr_u_fd(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

int	check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (base[0] == '\0')
		return (-1);
	while (base[i] != '\0')
	{
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j])
				return (-1);
			++j;
		}
		++i;
	}
	if (i < 2)
		return (-1);
	return (i);
}

void	check_exception(int nbr, char *base, int div)
{
	write(1, "-", 1);
	ft_putnbr_base(-(nbr / div), base);
	write(1, &base[-(nbr % div)], 1);
}

int	ft_numlen_base(unsigned long num, int base)
{
	int	len;

	if (num == 0)
		return (1);
	len = 0;
	while (num > 0)
	{
		num /= base;
		len++;
	}
	return (len);
}

void	ft_putnbr_base(unsigned long nbr, char *base)
{
	int		i;
	char	buffer[32];

	i = 0;
	if (nbr == 0)
	{
		write(1, &base[0], 1);
		return ;
	}
	while (nbr != 0)
	{
		buffer[i++] = base[nbr % 16];
		nbr = nbr / 16;
	}
	while (i > 0)
		write(1, &buffer[--i], 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:24:35 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/11 17:09:28 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memset(void *str, int c, int n)
{
	int				i;
	unsigned char	car;

	i = 0;
	car = (unsigned char)c;
	while (i < n)
	{
		((unsigned char *)str)[i] = car;
		i++;
	}
	return (str);
}

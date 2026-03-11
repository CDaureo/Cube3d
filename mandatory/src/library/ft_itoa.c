/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:33:17 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/11 17:08:16 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_reverse(char *arr, int start, int end)
{
	char	buff;

	while (start < end)
	{
		buff = arr[start];
		arr[start] = arr[end];
		arr[end] = buff;
		start++;
		end--;
	}
}

int	ft_count(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*transform(long nb, char *arr)
{
	size_t	i;

	i = 0;
	if (nb < 0)
	{
		arr[i++] = '-';
		nb = -nb;
	}
	if (nb == 0)
		arr[i++] = '0';
	while (nb != 0)
	{
		arr[i++] = (nb % 10) + '0';
		nb /= 10;
	}
	arr[i] = '\0';
	return (arr);
}

char	*ft_itoa(int n)
{
	char	*arr;
	long	nb;
	size_t	len;

	nb = n;
	len = ft_count(n);
	arr = malloc((len + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	arr = transform(nb, arr);
	if (n < 0)
		ft_reverse(arr, 1, ft_strlen(arr) - 1);
	else
		ft_reverse(arr, 0, ft_strlen(arr) - 1);
	return (arr);
}

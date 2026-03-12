/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:59:01 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/11 17:16:36 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_countwrds(char const *str, char delimiter)
{
	int	count;
	int	in_substr;
	int	i;

	count = 0;
	in_substr = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != delimiter && !in_substr)
		{
			count++;
			in_substr = 1;
		}
		else if (str[i] == delimiter)
		{
			in_substr = 0;
		}
		i++;
	}
	return (count);
}

void	fr_split(char **arr, int index)
{
	if (!arr[index])
	{
		while (index >= 0)
		{
			free(arr[index--]);
		}
		free(arr);
	}
}

char	**write_arr(char const*s, char c, int index, char **arr)
{
	int	len;
	int	start;

	len = 0;
	start = 0;
	while (s[start])
	{
		while (s[start] == c && s[start])
			start++;
		if (s[start] == '\0')
			break ;
		len = 0;
		while (s[start + len] != c && s[start + len] != '\0')
			len++;
		arr[index] = ft_substr(s, start, len);
		if (!arr[index])
		{
			fr_split(arr, index);
			return (NULL);
		}
		start += len;
		index++;
	}
	arr[index] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		numwrds;
	int		index;
	char	**arr;

	if (!s)
		return (NULL);
	index = 0;
	numwrds = ft_countwrds(s, c);
	arr = malloc((numwrds + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	return (write_arr(s, c, index, arr));
}

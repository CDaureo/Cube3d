/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:45:45 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/11 17:10:26 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*check(char *subs)
{
	if (!subs)
		return (0);
	subs[0] = '\0';
	return (subs);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;
	size_t	effective_len;

	i = 0;
	if (start >= ft_strlen(s))
	{
		subs = malloc(1 * sizeof(char));
		return (check(subs));
	}
	effective_len = ft_strlen(s) - start;
	if (!s)
		return (0);
	if (effective_len > len)
		effective_len = len;
	subs = malloc((effective_len + 1) * sizeof(char));
	if (!subs)
		return (0);
	while (i < effective_len && s[start + i] != '\0')
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

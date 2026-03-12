/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:26:10 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/11 17:18:26 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*s2;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	s2 = ft_substr(s1, start, end - start + 1);
	return (s2);
}

/*int	main(void)
{
	char	*s1 = "cocacola";
	char	*set = "cal";
	char 	*trimmed1 = ft_strtrim(s1, set);
	
	printf("Original: '%s'\nTrimmed: '%s'\n\n", s1, trimmed1);
}
*/
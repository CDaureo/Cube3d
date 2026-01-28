/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_trim.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:55:31 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/01/24 20:33:39 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*Elimina los espacios de al principio y al final de una cadena*/
char	*trim_whitespace(char *str)
{
	char	*end;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	if (*str == 0)
		return(str);
	end = str + ft_strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	*(end + 1) = '\0';
	return(str);
}

void trim_line(char *s)
{
    size_t i = 0;
    size_t len;

    if (!s)
        return;
    while (s[i] == ' ' || s[i] == '\t')
        i++;
    if (i > 0)
        memmove(s, s + i, ft_strlen(s + i) + 1);
    len = ft_strlen(s);
    if (len > 0 && s[len - 1] == '\n')
        s[len - 1] = '\0';
}
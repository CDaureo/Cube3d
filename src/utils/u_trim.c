/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:55:31 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/01/21 13:09:04 by cdaureo-         ###   ########.fr       */
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
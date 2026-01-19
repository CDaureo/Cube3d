/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:43:09 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/01/19 14:07:24 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*File Validator*/
int validate_extension(const char *file)
{
    size_t len;

	len = ft_strlen(file);
	if (!file)
		return (0);
	if (len < 4)
		return (0);
	if (ft_strcmp(file + len - 4, ".cub") == 0)
		return(1);
	return(0);    
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:08:09 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/01/24 20:46:23 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

int parse_map_line(char *line, t_map *map)
{
	char	*row;
	size_t	len;
	if (!line)
		return (0);
	row = ft_strdup(line);
	if (!row)
		return(printf("Error: Not enough memory dupping map row"), 0);
	len = ft_strlen(row);
	if (len > 0 && (row[len - 1] == '\n' || row[len - 1] == '\r'))
		row[len - 1] = '\0';

	if (!sanitize_row(row))
		return (free(row), printf("No valid character on map (sanitize): \"%s\"\n", row), 0);

	return (push_row(map, row));	
}

int finalize_map(t_map *map)
{
	int i;
	int len;
	char	*padded;

	i = 0;
	len = 0;
	while (i < map->height)
	{
		len = (int)ft_strlen(map->rows[i]);
		if (len < map->width)
		{
			padded = (char *)malloc(map->width + 1);
			if (!padded)
				return(printf("Error: Not enough memory normalize map"), 0);
			ft_memcpy(padded, map->rows[i], len);
			ft_memset(padded + len, ' ', map->width - len);
			padded[map->width] = '\0';
			free(map->rows[i]);
			map->rows[i] = padded;
		}
		i++;
	}
	return (1);
}
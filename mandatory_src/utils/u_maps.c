/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_maps.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:15:39 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/03/13 18:13:44 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_allow_chars(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == '\t'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D');
}

int	sanitize_row(const char *row)
{
	int	i;

	i = 0;
	if (!row)
		return (0);
	while (row[i])
	{
		if (row[i] == '\n' || row[i] == '\r')
		{
			i++;
			continue ;
		}
		if (!is_allow_chars(row[i]))
			return (0);
		i++;
	}
	return (1);
}

int	push_row(t_map *map, char *row_dup)
{
	char	**new_row;
	int		i;

	i = 0;
	new_row = (char **)malloc(sizeof(char *) * (map->height + 2));
	if (!new_row)
		return (printf("Error: Not enought memory.\n"));
	while (i < map->height)
	{
		new_row[i] = map->rows[i];
		i++;
	}
	new_row[i++] = row_dup;
	new_row[i] = NULL;
	free(map->rows);
	map->rows = new_row;
	map->height += 1;
	if ((int)ft_strlen(row_dup) > map->width)
		map->width = (int)ft_strlen(row_dup);
	return (1);
}

int	get_map_value(t_map *map, int x, int y, t_game *game)
{
	char	cell;
	t_door	*door;

	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (1);
	cell = map->rows[y][x];
	if (cell == '1')
		return (1);
	else if (cell == 'D')
	{
		door = find_door(game, x, y);
		if (door && door->is_open)
			return (0);
		else
			return (1);
	}
	else if (cell == '0' || cell == 'N'
		|| cell == 'S' || cell == 'E' || cell == 'W')
		return (0);
	else
		return (1);
}

int	print_map_line_error(char *trim, int started)
{
	if (started)
		return (printf("Error: línea inválida dentro del mapa: \"%s\"\n",
				trim), 0);
	return (printf("Error: línea inválida antes del mapa: \"%s\"\n", trim), 0);
}

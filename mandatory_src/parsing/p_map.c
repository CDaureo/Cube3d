/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:44:12 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/03/13 18:11:57 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_map_line(char *line, t_map *map)
{
	char	*row;
	size_t	len;

	if (!line)
		return (0);
	row = ft_strdup(line);
	if (!row)
		return (printf("Error: Not enough memory dupping map row"), 0);
	len = ft_strlen(row);
	if (len > 0 && (row[len - 1] == '\n' || row[len - 1] == '\r'))
		row[len - 1] = '\0';
	if (!sanitize_row(row))
		return (free(row), \
		printf("No valid character on map (sanitize): \"%s\"\n", row), 0);
	return (push_row(map, row));
}

int	finalize_map(t_map *map)
{
	int		i;
	int		len;
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
				return (printf("Error: Not enough memory normalize map"), 0);
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

static int	check_map_tile(t_map *map, int y, int x)
{
	char	c;

	c = map->rows[y][x];
	if (!is_playable_tile(c))
		return (1);
	if (y == 0 || x == 0)
		return (print_open_map_error(y, x));
	if (y == map->height - 1 || x == map->width - 1)
		return (print_open_map_error(y, x));
	if (has_space_around(map, y, x))
		return (print_open_map_error(y, x));
	return (1);
}

int	is_map_closed(t_map *map)
{
	int		y;
	int		x;

	if (!map || map->height <= 0 || map->width <= 0)
		return (printf("Error: map vacío o inválido\n"), 0);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!check_map_tile(map, y, x))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	parse_map(int fd, t_game *game)
{
	char	*line;
	int		started;
	int		status;

	started = 0;
	line = get_next_line(fd);
	while (line)
	{
		status = handle_map_line(line, game, &started);
		if (status == 0)
			return (0);
		if (status == 2)
			break ;
		line = get_next_line(fd);
	}
	if (!started)
		return (printf("Error: no se encontró ninguna fila de mapa\n"), 0);
	if (!finalize_map(&game->maps) || !is_map_closed(&game->maps))
		return (printf("Failed to parse map\n"), 0);
	return (1);
}

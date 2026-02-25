/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:28:03 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/02/25 12:33:30 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_player_char(char c, t_map *map, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		map->player_x = x;
		map->player_y = y;
		map->player_dir = c;
		return (1);
	}
	return (0);
}

int	validate_map_basic(t_map *map)
{
	int		players;
	int		x;
	int		y;

	players = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (is_player_char(map->rows[y][x], map, x, y))
				players++;
			x++;
		}
		y++;
	}
	if (players == 0)
		return (printf("Error\nNo se encontró posición inicial\n"), 0);
	if (players > 1)
		return (printf("Error\nMúltiples posiciones de jugador\n"), 0);
	return (1);
}

/**
 * Verifica si una celda es válida (dentro de límites y no es espacio)
 */
static int	is_valid_cell(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return (0);
	if (map->rows[y][x] == ' ')
		return (0);
	return (1);
}

/**
 * Valida que una celda transitable (0 o jugador) esté rodeada de paredes
 */
static int	check_cell_walls(t_map *map, int y, int x)
{
	if (!is_valid_cell(map, y - 1, x))
		return (0);
	if (!is_valid_cell(map, y + 1, x))
		return (0);
	if (!is_valid_cell(map, y, x - 1))
		return (0);
	if (!is_valid_cell(map, y, x + 1))
		return (0);
	return (1);
}

/**
 * Valida que el mapa esté completamente cerrado por paredes
 */
int	validate_map_closed(t_map *map)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			c = map->rows[y][x];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (!check_cell_walls(map, y, x))
				{
					printf("Error:\nMap not closed at: (%d, %d)\n", y, x);
					return (0);
				}
			}
			x++;
		}
		y++;
	}
	return (1);
}

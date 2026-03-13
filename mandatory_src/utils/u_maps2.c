/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_maps2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 18:06:52 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/03/13 18:14:10 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_playable_tile(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D')
		return (1);
	return (0);
}

int	has_space_around(t_map *map, int y, int x)
{
	if (map->rows[y - 1][x] == ' ' || map->rows[y + 1][x] == ' ')
		return (1);
	if (map->rows[y][x - 1] == ' ' || map->rows[y][x + 1] == ' ')
		return (1);
	return (0);
}

int	print_open_map_error(int y, int x)
{
	return (printf("Error\nMapa no cerrado %d,%d\n", y, x), 0);
}

int	handle_map_line(char *line, t_game *game, int *started)
{
	char	*trim;

	trim = trim_whitespace(line);
	if (trim[0] == '\0')
	{
		free(line);
		if (*started)
			return (2);
		return (1);
	}
	if (!sanitize_row(trim))
	{
		print_map_line_error(trim, *started);
		free(line);
		return (0);
	}
	if (!parse_map_line(line, &game->maps))
		return (free(line), 0);
	free(line);
	*started = 1;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_doors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:40:54 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/03/13 17:41:11 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	loop_doors(t_game *game, int door_index)
{
	while (game->y < game->maps.height)
	{
		game->x = 0;
		while (game->x < game->maps.width)
		{
			if (game->maps.rows[game->y][game->x] == 'D')
			{
				game->doors[door_index].x = game->x;
				game->doors[door_index].y = game->y;
				game->doors[door_index].is_open = 0;
				game->doors[door_index].open_progress = 0.0f;
				door_index++;
			}
			game->x++;
		}
		game->y++;
	}
}

void	parse_map_doors(t_game *game)
{
	int	door_count;
	int	door_index;

	game->y = 0;
	door_count = 0;
	while (game->y < game->maps.height)
	{
		game->x = 0;
		while (game->x < game->maps.width)
			door_count += (game->maps.rows[game->y][game->x++] == 'D');
		game->y++;
	}
	game->doors = malloc(sizeof(t_door) * door_count);
	game->door_count = door_count;
	door_index = 0;
	game->y = 0;
	loop_doors(game, door_index);
}

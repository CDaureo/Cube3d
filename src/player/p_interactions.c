/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_interactions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:52:33 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/19 13:53:54 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void initialize_player_from_map(t_mlx *mlx, t_map *map)
{
	mlx->posX = map->player_x + 0.5;
	mlx->posY = map->player_y + 0.5;
	mlx->pitch = 0;
	set_player_direction(mlx, map->player_dir, 0.80);
}

void interact_with_door(t_game *game)
{
	float distances[] = {0.3, 0.6, 0.9, 1.2, 1.5};
	int num_distances = 5;

	for (int i = 0; i < num_distances; i++)
	{
		float check_x = game->mlx.posX + game->mlx.dirX * distances[i];
		float check_y = game->mlx.posY + game->mlx.dirY * distances[i];
		int map_x = (int)check_x;
		int map_y = (int)check_y;

		if (map_x < 0 || map_x >= game->maps.width || 
			map_y < 0 || map_y >= game->maps.height)
			continue;
		if (game->maps.rows[map_y][map_x] == 'D')
		{
			t_door *door = find_door(game, map_x, map_y);
			if (door)
			{
				door->is_open = !door->is_open;
				printf("Door %s at (%d, %d)\n", 
					   door->is_open ? "opened" : "closed", map_x, map_y);
				return;
			}
		}
	}
}

void check_wall_hit(t_render *r, t_map *map, t_game *game)
{
	char cell;
	t_door *door;

	cell = map->rows[r->mapY][r->mapX];
	if (cell == '1')
	{
		r->hit = 1;
		r->hit_type = 1;
	}
	else if (cell == 'D')
	{
		door = find_door(game, r->mapX, r->mapY);
		if (door && !door->is_open)
		{
			r->hit = 1;
			r->hit_type = 2;
		}
	}
}


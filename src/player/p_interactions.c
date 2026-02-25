/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_interactions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:52:33 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/25 12:11:24 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	initialize_player_from_map(t_mlx *mlx, t_map *map)
{
	mlx->posX = map->player_x + 0.5;
	mlx->posY = map->player_y + 0.5;
	mlx->pitch = 0;
	set_player_direction(mlx, map->player_dir, 0.80);
}

void	interact_with_door(t_game *game)
{
	int		i;
	int		map_x;
	int		map_y;
	t_door	*door;

	i = -1;
	while (++i < 5)
	{
		map_x = (int)(game->mlx.posX + game->mlx.dirX * (0.3f + i * 0.3f));
		map_y = (int)(game->mlx.posY + game->mlx.dirY * (0.3f + i * 0.3f));
		door = find_door(game, map_x, map_y);
		if (map_x >= 0 && map_x < game->maps.width && \
			map_y >= 0 && map_y < game->maps.height && \
			game->maps.rows[map_y][map_x] == 'D' && door)
		{
			door->is_open = !door->is_open;
			door = find_door(game, map_x, map_y);
			return ;
		}
	}
}

void	check_wall_hit(t_render *r, t_map *map, t_game *game)
{
	char	cell;
	t_door	*door;

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

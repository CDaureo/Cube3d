/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_interactions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:52:33 by simgarci          #+#    #+#             */
/*   Updated: 2026/03/12 13:26:34 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	initialize_player_from_map(t_mlx *mlx, t_map *map)
{
	mlx->pos_x = map->player_x + 0.5;
	mlx->pos_y = map->player_y + 0.5;
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
		map_x = (int)(game->mlx.pos_x + game->mlx.dir_x * (0.3f + i * 0.3f));
		map_y = (int)(game->mlx.pos_y + game->mlx.dir_y * (0.3f + i * 0.3f));
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

	cell = map->rows[r->map_y][r->map_x];
	if (cell == '1')
	{
		r->hit = 1;
		r->hit_type = 1;
	}
	else if (cell == 'D')
	{
		door = find_door(game, r->map_x, r->map_y);
		if (door && !door->is_open)
		{
			r->hit = 1;
			r->hit_type = 2;
		}
	}
}

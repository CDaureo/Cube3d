/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_map_drawing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:43:53 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/25 17:51:16 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	background_check(t_minimap *mp, t_mlx *mlx, \
		t_game *game, t_map *map)
{
	double	map_scale;

	map_scale = 8.0;
	if (mp->distance_squared <= mp->radius * mp->radius)
	{
		mp->rel_x = mp->dx / (double)(MINIMAP_SIZE / 2);
		mp->rel_y = mp->dy / (double)(MINIMAP_SIZE / 2);
		mp->rotated_x = mp->rel_x * cos(mp->player_angle) - \
			mp->rel_y * sin(mp->player_angle);
		mp->rotated_y = mp->rel_x * sin(mp->player_angle) + \
				mp->rel_y * cos(mp->player_angle);
		mp->world_x = mlx->pos_x + mp->rotated_x * map_scale;
		mp->world_y = mlx->pos_y + mp->rotated_y * map_scale;
		mp->map_x = (int)mp->world_x;
		mp->map_y = (int)mp->world_y;
		if (get_map_value(map, mp->map_x, mp->map_y, game) == 1)
			mp->color = 0xFFFFFF;
		else
			mp->color = 0x333333;
		mp->spr_screen_x = mp->map_start_x + mp->pixel_x;
		mp->screen_y = mp->map_start_y + mp->pixel_y;
		if (mp->spr_screen_x < screen_width && mp->screen_y < screen_height)
			ft_mlx_pixel_put(mlx, mp->spr_screen_x, mp->screen_y, \
					mp->color);
	}
}

void	draw_map_background(t_minimap *mp, t_mlx *mlx, \
		t_map *map, t_game *game)
{
	mp->pixel_y = 0;
	while (mp->pixel_y < MINIMAP_SIZE)
	{
		mp->pixel_x = 0;
		while (mp->pixel_x < MINIMAP_SIZE)
		{
			mp->dx = mp->pixel_x - MINIMAP_SIZE / 2;
			mp->dy = mp->pixel_y - MINIMAP_SIZE / 2;
			mp->distance_squared = mp->dx * \
				mp->dx + mp->dy * mp->dy;
			background_check(mp, mlx, game, map);
			mp->pixel_x++;
		}
		mp->pixel_y++;
	}
}

void	draw_minimap_circle(t_mlx *mlx, t_minimap *mp)
{
	mp->angle = 0;
	while (mp->angle < 360)
	{
		mp->radian = mp->angle * M_PI / 180.0;
		mp->border_x = mp->center_x + \
			(int)(cos(mp->radian) * mp->radius);
		mp->border_y = mp->center_y + \
		(int)(sin(mp->radian) * mp->radius);
		if (mp->border_x >= 0 && mp->border_y >= 0 && \
			mp->border_x < screen_width && \
				mp->border_y < screen_height)
			ft_mlx_pixel_put(mlx, mp->border_x, \
				mp->border_y, 0xFFFFFF);
		mp->inner_border_x = mp->center_x + \
			(int)(cos(mp->radian) * (mp->radius - 1));
		mp->inner_border_y = mp->center_y + \
			(int)(sin(mp->radian) * (mp->radius - 1));
		if (mp->inner_border_x >= 0 && mp->inner_border_y >= 0 && \
				mp->inner_border_x < screen_width && \
					mp->inner_border_y < screen_height)
			ft_mlx_pixel_put(mlx, mp->inner_border_x, \
					mp->inner_border_y, 0xFFFFFF);
		mp->angle++;
	}
}

void	draw_player_dot(t_mlx *mlx, t_minimap *mp)
{
	ft_mlx_pixel_put(mlx, mp->player_pixel_x, \
			mp->player_pixel_y, 0xFFFF00);
}

void	draw_minimap(t_mlx *mlx, t_map *map, t_game *game)
{
	t_minimap	mp;

	init_minimap(&mp, mlx);
	draw_map_background(&mp, mlx, map, game);
	draw_arrow_body(mlx, &mp);
	draw_arrow_outline(mlx, &mp);
	draw_player_dot(mlx, &mp);
	draw_minimap_circle(mlx, &mp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_minimap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:02:01 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/19 14:05:54 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void init_minimap(t_minimap *minimap, t_mlx *mlx)
{
	minimap->map_start_x = screenWidth - MINIMAP_SIZE - MINIMAP_OFFSET;
	minimap->map_start_y = screenHeight - MINIMAP_SIZE - MINIMAP_OFFSET;
	minimap->center_x = minimap->map_start_x + MINIMAP_SIZE / 2;
	minimap->center_y = minimap->map_start_y + MINIMAP_SIZE / 2;
	minimap->radius = MINIMAP_SIZE / 2;
	minimap->player_pixel_x = minimap->center_x;
	minimap->player_pixel_y = minimap->center_y;
	minimap->player_angle = atan2(mlx->dirY, mlx->dirX) + M_PI/2;  // Was - M_PI/2
	minimap->arrow_length = 6;
	minimap->arrow_width = 4;
}

static void draw_dot(t_mlx *mlx, int dot_size, int center_x, int center_y)
{
	int y;
	int x;
	int pixel_x;
	int pixel_y;

	y = -dot_size;
	while(y <= dot_size)
	{
		x = -dot_size;
		while(x <= dot_size)
		{
			if(x*x + y*y <= dot_size*dot_size)
			{
				pixel_x = center_x + x;
				pixel_y = center_y + y;
				if(pixel_x >= 0 && pixel_y >= 0 && pixel_x < screenWidth && pixel_y < screenHeight)
				{
					ft_mlx_pixel_put(mlx, pixel_x, pixel_y, 0xFFFFFF);
				}
			}
			x++;
		}
		y++;
	}
}

void draw_crosshair(t_mlx *mlx)
{
	t_minimap map;

	map.center_x = screenWidth / 2;
	map.center_y = screenHeight / 2;
	map.dot_size = 2;
	map.outline_size = map.dot_size + 1;
	map.y = -map.outline_size;
	while(map.y <= map.outline_size)
	{
		while(map.x <= map.outline_size)
		{
			map.x = -map.outline_size;
			if(map.x*map.x + map.y*map.y <= map.outline_size*map.outline_size)
			{
				map.pixel_x = map.center_x + map.x;
				map.pixel_y = map.center_y + map.y;
				if(map.pixel_x >= 0 && map.pixel_y >= 0 && map.pixel_x < screenWidth && map.pixel_y < screenHeight)
					ft_mlx_pixel_put(mlx, map.pixel_x, map.pixel_y, 0x000000);
			}
			map.x++;
		}
		map.y++;
	}
	draw_dot(mlx, map.dot_size, map.center_x, map.center_y);
}

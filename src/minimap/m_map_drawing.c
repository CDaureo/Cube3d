/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_map_drawing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:43:53 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/18 14:44:20 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


void background_check(t_minimap *minimap, t_mlx *mlx, t_game *game, t_map *map)
{
	if(minimap->distance_squared <= minimap->radius * minimap->radius)
	{
		minimap->rel_x = minimap->dx / (double)(MINIMAP_SIZE / 2);
		minimap->rel_y = minimap->dy / (double)(MINIMAP_SIZE / 2);
		minimap->rotated_x = minimap->rel_x * cos(minimap->player_angle) - minimap->rel_y * sin(minimap->player_angle);
		minimap->rotated_y = minimap->rel_x * sin(minimap->player_angle) + minimap->rel_y * cos(minimap->player_angle);
		double map_scale = 8.0;
		minimap->world_x = mlx->posX + minimap->rotated_x * map_scale;   
		minimap->world_y = mlx->posY + minimap->rotated_y * map_scale;  
		minimap->map_x = (int)minimap->world_x;
		minimap->map_y = (int)minimap->world_y;
		if(get_map_value(map, minimap->map_x, minimap->map_y, game) == 1)
			minimap->color = 0xFFFFFF;
		else
			minimap->color = 0x333333;
		minimap->screen_x = minimap->map_start_x + minimap->pixel_x;
		minimap->screen_y = minimap->map_start_y + minimap->pixel_y;
		if(minimap->screen_x < screenWidth && minimap->screen_y < screenHeight)
			ft_mlx_pixel_put(mlx, minimap->screen_x, minimap->screen_y, minimap->color);
	}
}

void draw_map_background(t_minimap *minimap, t_mlx *mlx, t_map *map, t_game *game)
{ 
	minimap->pixel_y = 0;

	while(minimap->pixel_y < MINIMAP_SIZE)
	{
		minimap->pixel_x = 0;
		while(minimap->pixel_x < MINIMAP_SIZE)
		{	   
			minimap->dx = minimap->pixel_x - MINIMAP_SIZE / 2;
			minimap->dy = minimap->pixel_y - MINIMAP_SIZE / 2;
			minimap->distance_squared = minimap->dx * minimap->dx + minimap->dy * minimap->dy;
			background_check(minimap, mlx, game, map);
			minimap->pixel_x++;
		}
		minimap->pixel_y++;
	}
}


void draw_minimap_circle(t_mlx *mlx, t_minimap *minimap)
{
	minimap->angle = 0;

	while(minimap->angle < 360)
	{  
		minimap->radian = minimap->angle * M_PI / 180.0;
		minimap->border_x = minimap->center_x + (int)(cos(minimap->radian) * minimap->radius);
		minimap->border_y = minimap->center_y + (int)(sin(minimap->radian) * minimap->radius);
		if(minimap->border_x >= 0 && minimap->border_y >= 0 && minimap->border_x < screenWidth && minimap->border_y < screenHeight)
			ft_mlx_pixel_put(mlx, minimap->border_x, minimap->border_y, 0xFFFFFF);
		minimap->inner_border_x = minimap->center_x + (int)(cos(minimap->radian) * (minimap->radius - 1));
		minimap->inner_border_y = minimap->center_y + (int)(sin(minimap->radian) * (minimap->radius - 1));
		if(minimap->inner_border_x >= 0 && minimap->inner_border_y >= 0 && minimap->inner_border_x < screenWidth && minimap->inner_border_y < screenHeight)
			ft_mlx_pixel_put(mlx, minimap->inner_border_x, minimap->inner_border_y, 0xFFFFFF);
			
		minimap->angle++;
	}
}

void draw_player_dot(t_mlx *mlx, t_minimap *minimap)
{
	ft_mlx_pixel_put(mlx, minimap->player_pixel_x, minimap->player_pixel_y, 0xFFFF00);
}

void draw_minimap(t_mlx *mlx, t_map *map, t_game *game)
{
	t_minimap minimap;
	init_minimap(&minimap, mlx);
	draw_map_background(&minimap, mlx, map, game);
	draw_arrow_body(mlx, &minimap);
	draw_arrow_outline(mlx, &minimap);   
	draw_player_dot(mlx, &minimap);
	draw_minimap_circle(mlx, &minimap);
}

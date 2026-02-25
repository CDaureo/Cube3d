/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_rendering.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:05:08 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/25 13:39:27 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void calculate_sprite_transform(t_mlx *mlx, t_sprite *sprite, t_sprite_system *sprites)
{
	sprites->spr_x = sprite->x - mlx->pos_x;
	sprites->spr_y = sprite->y - mlx->pos_y;
	sprites->inv_det = 1.0 / (mlx->plane_x * mlx->dir_y - mlx->dir_x * mlx->plane_y);
	sprites->transform_x = sprites->inv_det * (mlx->dir_y * sprites->spr_x - mlx->dir_x * sprites->spr_y);
	sprites->transform_y = sprites->inv_det * (-mlx->plane_y * sprites->spr_x + mlx->plane_x * sprites->spr_y);
}

void calculate_sprite_screen_coords(t_mlx *mlx, t_sprite_system *sprites)
{
	sprites->spr_screen_x = (int)((SCREENWIDTH / 2) * (1 + sprites->transform_x / sprites->transform_y));
	sprites->spr_height = abs((int)(SCREENHEIGHT / sprites->transform_y)) / 8;
	sprites->spr_width = abs((int)(SCREENHEIGHT / sprites->transform_y)) / 6;
	sprites->horizon_y = SCREENHEIGHT / 2 + (int)mlx->pitch;
	sprites->ground_y = sprites->horizon_y + (int)(SCREENHEIGHT / (2.0 * sprites->transform_y));
}

void calculate_sprite_draw_bounds(t_sprite_system *sprites)
{
	sprites->draw_s_y = sprites->ground_y - sprites->spr_height;
	sprites->draw_e_y = sprites->ground_y;
	if (sprites->draw_s_y < 0)
		sprites->draw_s_y = 0;
	if (sprites->draw_e_y >= SCREENHEIGHT)
		sprites->draw_e_y = SCREENHEIGHT - 1;
	sprites->draw_s_x = -sprites->spr_width / 2 + sprites->spr_screen_x;
	if (sprites->draw_s_x < 0)
		sprites->draw_s_x = 0;
	sprites->draw_e_x = sprites->spr_width / 2 + sprites->spr_screen_x;
	if (sprites->draw_e_x >= SCREENWIDTH)
		sprites->draw_e_x = SCREENWIDTH - 1;
}

void render_sprite_column(t_mlx *mlx, t_sprite_system *sprites, char *grass_data, int stripe)
{
	int y;

	sprites->tex_x = (int)((stripe - sprites->draw_s_x) * sprites->grass_width / (sprites->draw_e_x - sprites->draw_s_x));
	if (sprites->tex_x < 0)
		sprites->tex_x = 0;
	if (sprites->tex_x >= sprites->grass_width)
		sprites->tex_x = sprites->grass_width - 1;
	y = sprites->draw_s_y;
	while(y < sprites->draw_e_y)
	{
		sprites->tex_y = (int)((y - sprites->draw_s_y) * sprites->grass_height / (sprites->draw_e_y - sprites->draw_s_y));
		if (sprites->tex_y < 0) sprites->tex_y = 0;
		if (sprites->tex_y >= sprites->grass_height) sprites->tex_y = sprites->grass_height - 1;
		sprites->color = get_sprite_pixel(grass_data, sprites->tex_x, sprites->tex_y, sprites);
		if (sprites->color == 0xFF00FF || (sprites->color & 0xFF00FF) == 0xFF00FF) 
		{
			y++;
			continue;
		}
		if (stripe >= 0 && stripe < SCREENWIDTH && y >= 0 && y < SCREENHEIGHT)
			ft_mlx_pixel_put(mlx, stripe, y, sprites->color);
		y++;
	}
}

void render_single_sprite(t_mlx *mlx, t_sprite *sprite, t_sprite_system *sprites)
{
	int stripe;
	char *current_grass_data;

	calculate_sprite_transform(mlx, sprite, sprites);
	if (sprites->transform_y <= 0)
		return;
	calculate_sprite_screen_coords(mlx, sprites);
	calculate_sprite_draw_bounds(sprites);
	if (sprites->draw_s_y >= sprites->draw_e_y || sprites->draw_s_x >= sprites->draw_e_x)
		return;
	current_grass_data = sprites->grass_data[sprite->texture_index];
	stripe = sprites->draw_s_x;
	while(stripe < sprites->draw_e_x)
	{
		if (stripe >= 0 && stripe < SCREENWIDTH && sprites->transform_y > mlx->zbuffer[stripe]) 
		{
			stripe++;
			continue;
		}
		render_sprite_column(mlx, sprites, current_grass_data, stripe);
		stripe++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_rendering.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:05:08 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/18 17:05:19 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void calculate_sprite_transform(t_mlx *mlx, t_sprite *sprite, t_sprite_system *sprites)
{
	sprites->spriteX = sprite->x - mlx->posX;
	sprites->spriteY = sprite->y - mlx->posY;
	sprites->invDet = 1.0 / (mlx->planeX * mlx->dirY - mlx->dirX * mlx->planeY);
	sprites->transformX = sprites->invDet * (mlx->dirY * sprites->spriteX - mlx->dirX * sprites->spriteY);
	sprites->transformY = sprites->invDet * (-mlx->planeY * sprites->spriteX + mlx->planeX * sprites->spriteY);
}

void calculate_sprite_screen_coords(t_mlx *mlx, t_sprite_system *sprites)
{
	sprites->spriteScreenX = (int)((screenWidth / 2) * (1 + sprites->transformX / sprites->transformY));
	sprites->spriteHeight = abs((int)(screenHeight / sprites->transformY)) / 8;
	sprites->spriteWidth = abs((int)(screenHeight / sprites->transformY)) / 6;
	sprites->horizonY = screenHeight / 2 + (int)mlx->pitch;
	sprites->groundY = sprites->horizonY + (int)(screenHeight / (2.0 * sprites->transformY));
}

void calculate_sprite_draw_bounds(t_sprite_system *sprites)
{
	sprites->drawStartY = sprites->groundY - sprites->spriteHeight;
	sprites->drawEndY = sprites->groundY;
	if (sprites->drawStartY < 0)
		sprites->drawStartY = 0;
	if (sprites->drawEndY >= screenHeight)
		sprites->drawEndY = screenHeight - 1;
	sprites->drawStartX = -sprites->spriteWidth / 2 + sprites->spriteScreenX;
	if (sprites->drawStartX < 0)
		sprites->drawStartX = 0;
	sprites->drawEndX = sprites->spriteWidth / 2 + sprites->spriteScreenX;
	if (sprites->drawEndX >= screenWidth)
		sprites->drawEndX = screenWidth - 1;
}

void render_sprite_column(t_mlx *mlx, t_sprite_system *sprites, char *grass_data, int stripe)
{
	int y;

	sprites->texX = (int)((stripe - sprites->drawStartX) * sprites->grass_width / (sprites->drawEndX - sprites->drawStartX));
	if (sprites->texX < 0)
		sprites->texX = 0;
	if (sprites->texX >= sprites->grass_width)
		sprites->texX = sprites->grass_width - 1;
	y = sprites->drawStartY;
	while(y < sprites->drawEndY)
	{
		sprites->texY = (int)((y - sprites->drawStartY) * sprites->grass_height / (sprites->drawEndY - sprites->drawStartY));
		if (sprites->texY < 0) sprites->texY = 0;
		if (sprites->texY >= sprites->grass_height) sprites->texY = sprites->grass_height - 1;
		sprites->color = get_sprite_pixel(grass_data, sprites->texX, sprites->texY, sprites);
		if (sprites->color == 0xFF00FF || (sprites->color & 0xFF00FF) == 0xFF00FF) 
		{
			y++;
			continue;
		}
		if (stripe >= 0 && stripe < screenWidth && y >= 0 && y < screenHeight)
			ft_mlx_pixel_put(mlx, stripe, y, sprites->color);
		y++;
	}
}

void render_single_sprite(t_mlx *mlx, t_sprite *sprite, t_sprite_system *sprites)
{
	int stripe;
	char *current_grass_data;

	calculate_sprite_transform(mlx, sprite, sprites);
	if (sprites->transformY <= 0)
		return;
	calculate_sprite_screen_coords(mlx, sprites);
	calculate_sprite_draw_bounds(sprites);
	if (sprites->drawStartY >= sprites->drawEndY || sprites->drawStartX >= sprites->drawEndX)
		return;
	current_grass_data = sprites->grass_data[sprite->texture_index];
	stripe = sprites->drawStartX;
	while(stripe < sprites->drawEndX)
	{
		if (stripe >= 0 && stripe < screenWidth && sprites->transformY > mlx->zbuffer[stripe]) 
		{
			stripe++;
			continue;
		}
		render_sprite_column(mlx, sprites, current_grass_data, stripe);
		stripe++;
	}
}

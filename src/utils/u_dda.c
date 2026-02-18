/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_dda.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:03:58 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/18 17:04:27 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void update_vars(t_render *r, t_mlx *mlx, double fov_scale)
{
	r->lineHeight = (int)(screenHeight / r->perpWallDist * fov_scale);
	r->horizon = screenHeight / 2 + mlx->pitch;
	r->drawStart = -r->lineHeight / 2 + r->horizon;
	r->drawEnd = r->lineHeight / 2 + r->horizon;
}

void data_update(t_mlx *mlx, t_render *r, t_game *game)
{
	double fov_scale = 1.0;
	double wallX;

	if(r->side == 0) 
		r->perpWallDist = (r->sideDistX - r->deltaDistX);
	else		  
		r->perpWallDist = (r->sideDistY - r->deltaDistY);
	if(r->perpWallDist <= 0.001)
		r->perpWallDist = 0.001;
	update_vars(r, mlx, fov_scale);
	if(r->drawStart < 0) r->drawStart = 0;
	if(r->drawEnd >= screenHeight) r->drawEnd = screenHeight - 1;
	if (r->side == 0)
		wallX = mlx->posY + r->perpWallDist * r->rayDirY;
	else
		wallX = mlx->posX + r->perpWallDist * r->rayDirX;
	wallX -= floor(wallX);
	r->texX = (int)(wallX * (double)game->textures.tex_width);
	if (r->side == 0 && r->rayDirX > 0)
		r->texX = game->textures.tex_width - r->texX - 1;
	if (r->side == 1 && r->rayDirY < 0)
		r->texX = game->textures.tex_width - r->texX - 1;
	r->step = 1.0 * game->textures.tex_height / r->lineHeight;
	r->texPos = (r->drawStart - r->horizon + r->lineHeight / 2) * r->step;
	r->y = 0;
}

void vertical_loop(t_mlx *mlx, t_render *r, t_game *game, char *texture_data)
{
	int y;
	int tex_y;
	int color;

	y = r->drawStart;
	r->texPos = (r->drawStart - r->horizon + r->lineHeight / 2) * r->step;
	while (y <= r->drawEnd)
	{
		tex_y = (int)r->texPos % game->textures.tex_height;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= game->textures.tex_height)
			tex_y = game->textures.tex_height - 1;
		r->texPos += r->step;
		color = get_texture_pixel(texture_data, r->texX, tex_y, &game->textures);
		if (r->side == 1)
			color = ((((color >> 16) & 0xFF) * 9 / 10) << 16) | 
					((((color >> 8) & 0xFF) * 9 / 10) << 8) | 
					(((color & 0xFF) * 9 / 10));
		if (y >= 0 && y < screenHeight)
			ft_mlx_pixel_put(mlx, r->x, y, color);
		y++;
	}
}

void vertical_update(t_mlx *mlx, t_render *r, t_game *game)
{
	char *texture_data;

	if (r->hit_type == 2)
		texture_data = game->textures.data[4];
	else
		texture_data = get_wall_texture_fast(r, &game->textures);
	vertical_loop(mlx, r, game, texture_data);
}

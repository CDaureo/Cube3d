/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_dda.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:03:58 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/25 13:42:54 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void update_vars(t_render *r, t_mlx *mlx, double fov_scale)
{
	r->line_height = (int)(SCREENHEIGHT / r->perp_wall_dist * fov_scale);
	r->horizon = SCREENHEIGHT / 2 + mlx->pitch;
	r->draw_start = -r->line_height / 2 + r->horizon;
	r->draw_end = r->line_height / 2 + r->horizon;
}

void data_update(t_mlx *mlx, t_render *r, t_game *game)
{
	double fov_scale = 1.0;
	double wallX;

	if(r->side == 0) 
		r->perp_wall_dist = (r->side_dist_x - r->delta_dits_x);
	else
		r->perp_wall_dist = (r->side_dist_y - r->delta_dits_y);
	if (r->perp_wall_dist <= 0.001)
		r->perp_wall_dist = 0.001;
	update_vars(r, mlx, fov_scale);
	if (r->draw_start < 0) r->draw_start = 0;
	if (r->draw_end >= SCREENHEIGHT) r->draw_end = SCREENHEIGHT - 1;
	if (r->side == 0)
		wallX = mlx->pos_y + r->perp_wall_dist * r->raydir_y;
	else
		wallX = mlx->pos_x + r->perp_wall_dist * r->raydir_x;
	wallX -= floor(wallX);
	r->tex_x = (int)(wallX * (double)game->textures.tex_width);
	if (r->side == 0 && r->raydir_x > 0)
		r->tex_x = game->textures.tex_width - r->tex_x - 1;
	if (r->side == 1 && r->raydir_y < 0)
		r->tex_x = game->textures.tex_width - r->tex_x - 1;
	r->step = 1.0 * game->textures.tex_height / r->line_height;
	r->tex_pos = (r->draw_start - r->horizon + r->line_height / 2) * r->step;
	r->y = 0;
}

void vertical_loop(t_mlx *mlx, t_render *r, t_game *game, char *texture_data)
{
	int y;
	int tex_y;
	int color;

	y = r->draw_start;
	r->tex_pos = (r->draw_start - r->horizon + r->line_height / 2) * r->step;
	while (y <= r->draw_end)
	{
		tex_y = (int)r->tex_pos % game->textures.tex_height;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= game->textures.tex_height)
			tex_y = game->textures.tex_height - 1;
		r->tex_pos += r->step;
		color = get_texture_pixel(texture_data, r->tex_x, tex_y, &game->textures);
		if (r->side == 1)
			color = ((((color >> 16) & 0xFF) * 9 / 10) << 16) | 
					((((color >> 8) & 0xFF) * 9 / 10) << 8) | 
					(((color & 0xFF) * 9 / 10));
		if (y >= 0 && y < SCREENHEIGHT)
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

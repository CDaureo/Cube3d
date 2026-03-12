/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_dda.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:55:34 by simgarci          #+#    #+#             */
/*   Updated: 2026/03/12 13:26:34 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	update_vars(t_render *r, t_mlx *mlx, double fov_scale)
{
	r->line_height = (int)(SCREEN_HEIGHT) / r->perp_wall_dist * fov_scale;
	r->horizon = SCREEN_HEIGHT / 2 + mlx->pitch;
	r->draw_start = -r->line_height / 2 + r->horizon;
	r->draw_end = r->line_height / 2 + r->horizon;
}

void	calculate_wall_distance(t_mlx *mlx, t_render *r)
{
	double	fov_scale;

	fov_scale = 1.0;
	if (r->side == 0)
		r->perp_wall_dist = (r->side_dist_x - r->delta_dits_x);
	else
		r->perp_wall_dist = (r->side_dist_y - r->delta_dits_y);
	if (r->perp_wall_dist <= 0.001)
		r->perp_wall_dist = 0.001;
	update_vars(r, mlx, fov_scale);
	if (r->draw_start < 0)
		r->draw_start = 0;
	if (r->draw_end >= SCREEN_HEIGHT)
		r->draw_end = SCREEN_HEIGHT - 1;
}

void	calculate_texture_coords(t_mlx *mlx, t_render *r, t_game *game)
{
	double	wall_x;

	if (r->side == 0)
		wall_x = mlx->pos_y + r->perp_wall_dist * r->raydir_y;
	else
		wall_x = mlx->pos_x + r->perp_wall_dist * r->raydir_x;
	wall_x -= floor(wall_x);
	r->tex_x = (int)(wall_x * (double)game->txt.tex_width);
	if (r->side == 0 && r->raydir_x > 0)
		r->tex_x = game->txt.tex_width - r->tex_x - 1;
	if (r->side == 1 && r->raydir_y < 0)
		r->tex_x = game->txt.tex_width - r->tex_x - 1;
	r->step = 1.0 * game->txt.tex_height / r->line_height;
	r->tex_pos = (r->draw_start - r->horizon + r->line_height / 2) * r->step;
	r->y = 0;
}

void	vertical_loop(t_mlx *mlx, t_render *r, t_game *game, char *texture_data)
{
	int	y;
	int	tex_y;
	int	color;

	y = r->draw_start;
	r->tex_pos = (r->draw_start - r->horizon + r->line_height / 2) * r->step;
	while (y <= r->draw_end)
	{
		tex_y = (int)r->tex_pos % game->txt.tex_height;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= game->txt.tex_height)
			tex_y = game->txt.tex_height - 1;
		r->tex_pos += r->step;
		color = get_texture_pixel(texture_data, r->tex_x, tex_y, &game->txt);
		if (r->side == 1)
			color = ((((color >> 16) & 0xFF) * 9 / 10) << 16) | \
					((((color >> 8) & 0xFF) * 9 / 10) << 8) | \
					(((color & 0xFF) * 9 / 10));
		if (y >= 0 && y < SCREEN_HEIGHT)
			ft_mlx_pixel_put(mlx, r->x, y, color);
		y++;
	}
}

void	vertical_update(t_mlx *mlx, t_render *r, t_game *game)
{
	char	*texture_data;

	if (r->hit_type == 2)
		texture_data = game->txt.data[4];
	else
		texture_data = get_wall_texture_fast(r, &game->txt);
	vertical_loop(mlx, r, game, texture_data);
}

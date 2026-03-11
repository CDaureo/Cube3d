/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_rendering_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 18:18:48 by simgarci          #+#    #+#             */
/*   Updated: 2026/03/11 18:19:04 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_spr_transform(t_mlx *mlx, t_spr_system *spr)
{
	spr->spr_x = spr->spr_x - mlx->pos_x;
	spr->spr_y = spr->spr_y - mlx->pos_y;
	spr->inv_det = 1.0 / (mlx->plane_x * mlx->dir_y - \
			mlx->dir_x * mlx->plane_y);
	spr->transform_x = spr->inv_det * \
		(mlx->dir_y * spr->spr_x - mlx->dir_x * spr->spr_y);
	spr->transform_y = spr->inv_det * \
		(-mlx->plane_y * spr->spr_x + mlx->plane_x * spr->spr_y);
}

void	calculate_spr_screen_coords(t_mlx *mlx, t_spr_system *spr)
{
	spr->spr_screen_x = (int)((SCREEN_WIDTH / 2) * \
		(1 + spr->transform_x / spr->transform_y));
	spr->spr_height = abs((int)(SCREEN_HEIGHT / spr->transform_y)) / 8;
	spr->spr_width = abs((int)(SCREEN_HEIGHT / spr->transform_y)) / 6;
	spr->horizon_y = SCREEN_HEIGHT / 2 + (int)mlx->pitch;
	spr->ground_y = spr->horizon_y + \
		(int)(SCREEN_HEIGHT / (2.0 * spr->transform_y));
}

void	calculate_spr_draw_bounds(t_spr_system *spr)
{
	spr->draw_s_y = spr->ground_y - spr->spr_height;
	spr->draw_e_y = spr->ground_y;
	if (spr->draw_s_y < 0)
		spr->draw_s_y = 0;
	if (spr->draw_e_y >= SCREEN_HEIGHT)
		spr->draw_e_y = SCREEN_HEIGHT - 1;
	spr->draw_s_x = -spr->spr_width / 2 + spr->spr_screen_x;
	if (spr->draw_s_x < 0)
		spr->draw_s_x = 0;
	spr->draw_e_x = spr->spr_width / 2 + spr->spr_screen_x;
	if (spr->draw_e_x >= SCREEN_WIDTH)
		spr->draw_e_x = SCREEN_WIDTH - 1;
}

void	render_sprite_column(t_mlx *mlx, t_spr_system *spr, \
		char *grass_data, int stripe)
{
	int	y;

	spr->tex_x = (int)((stripe - spr->draw_s_x) * \
		spr->grass_width / (spr->draw_e_x - spr->draw_s_x));
	if (spr->tex_x < 0)
		spr->tex_x = 0;
	else if (spr->tex_x >= spr->grass_width)
		spr->tex_x = spr->grass_width - 1;
	y = spr->draw_s_y;
	while (y < spr->draw_e_y)
	{
		spr->tex_y = (int)((y - spr->draw_s_y) * \
			spr->grass_height / (spr->draw_e_y - spr->draw_s_y));
		if (spr->tex_y < 0)
			spr->tex_y = 0;
		else if (spr->tex_y >= spr->grass_height)
			spr->tex_y = spr->grass_height - 1;
		spr->color = get_spr_pixel(grass_data, spr->tex_x, spr->tex_y, spr);
		if (!(spr->color == 0xFF00FF || (spr->color & 0xFF00FF) == 0xFF00FF) \
			&& stripe >= 0 && stripe \
			< SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
			ft_mlx_pixel_put(mlx, stripe, y, spr->color);
		y++;
	}
}

void	render_single_spr(t_mlx *mlx, t_spr *sprs, t_spr_system *spr)
{
	int		stripe;
	char	*current_grass_data;

	spr->spr_x = sprs->x;
	spr->spr_y = sprs->y;
	calculate_spr_transform(mlx, spr);
	if (spr->transform_y <= 0)
		return ;
	calculate_spr_screen_coords(mlx, spr);
	calculate_spr_draw_bounds(spr);
	if (spr->draw_s_y >= spr->draw_e_y || spr->draw_s_x >= spr->draw_e_x)
		return ;
	current_grass_data = spr->grass_data[sprs->texture_index];
	stripe = spr->draw_s_x;
	while (stripe < spr->draw_e_x)
	{
		if (stripe >= 0 && stripe < SCREEN_WIDTH && \
				spr->transform_y > mlx->zbuffer[stripe])
		{
			stripe++;
			continue ;
		}
		render_sprite_column(mlx, spr, current_grass_data, stripe);
		stripe++;
	}
}

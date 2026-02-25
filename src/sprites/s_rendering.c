/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_rendering.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:05:08 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/25 12:52:08 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_spr_transform(t_mlx *mlx, t_spr *spr, t_spr_system *sprs)
{
	sprs->sprX = spr->x - mlx->posX;
	sprs->sprY = spr->y - mlx->posY;
	sprs->invDet = 1.0 / (mlx->planeX * mlx->dirY - mlx->dirX * mlx->planeY);
	sprs->transformX = sprs->invDet * \
		(mlx->dirY * sprs->sprX - mlx->dirX * sprs->sprY);
	sprs->transformY = sprs->invDet * \
		(-mlx->planeY * sprs->sprX + mlx->planeX * sprs->sprY);
}

void	calculate_spr_screen_coords(t_mlx *mlx, t_spr_system *sprs)
{
	sprs->sprScreenX = (int)((screenWidth / 2) * \
		(1 + sprs->transformX / sprs->transformY));
	sprs->sprHeight = abs((int)(screenHeight / sprs->transformY)) / 8;
	sprs->sprWidth = abs((int)(screenHeight / sprs->transformY)) / 6;
	sprs->horizonY = screenHeight / 2 + (int)mlx->pitch;
	sprs->groundY = sprs->horizonY + \
		(int)(screenHeight / (2.0 * sprs->transformY));
}

void	calculate_spr_draw_bounds(t_spr_system *sprs)
{
	sprs->drawStartY = sprs->groundY - sprs->sprHeight;
	sprs->drawEndY = sprs->groundY;
	if (sprs->drawStartY < 0)
		sprs->drawStartY = 0;
	if (sprs->drawEndY >= screenHeight)
		sprs->drawEndY = screenHeight - 1;
	sprs->drawStartX = -sprs->sprWidth / 2 + sprs->sprScreenX;
	if (sprs->drawStartX < 0)
		sprs->drawStartX = 0;
	sprs->drawEndX = sprs->sprWidth / 2 + sprs->sprScreenX;
	if (sprs->drawEndX >= screenWidth)
		sprs->drawEndX = screenWidth - 1;
}

void	render_spr_column(t_mlx *mlx, t_spr_system *sprs, \
		char *grass_data, int stripe)
{
	int	y;

	sprs->texX = (int)((stripe - sprs->drawStartX) * \
		sprs->grass_width / (sprs->drawEndX - sprs->drawStartX));
	if (sprs->texX < 0)
		sprs->texX = 0;
	if (sprs->texX >= sprs->grass_width)
		sprs->texX = sprs->grass_width - 1;
	y = sprs->drawStartY;
	while (y < sprs->drawEndY)
	{
		sprs->texY = (int)((y - sprs->drawStartY) * \
			sprs->grass_height / (sprs->drawEndY - sprs->drawStartY));
		if (sprs->texY < 0)
			sprs->texY = 0;
		if (sprs->texY >= sprs->grass_height)
			sprs->texY = sprs->grass_height - 1;
		sprs->color = get_spr_pixel(grass_data, \
				sprs->texX, sprs->texY, sprs);
		if (sprs->color == 0xFF00FF || (sprs->color & 0xFF00FF) == 0xFF00FF)
		{
			y++;
			continue ;
		}
		if (stripe >= 0 && stripe < screenWidth && y >= 0 && y < screenHeight)
			ft_mlx_pixel_put(mlx, stripe, y, sprs->color);
		y++;
	}
}

void	render_single_spr(t_mlx *mlx, t_spr *spr, t_spr_system *sprs)
{
	int		stripe;
	char	*current_grass_data;

	calculate_spr_transform(mlx, spr, sprs);
	if (sprs->transformY <= 0)
		return ;
	calculate_spr_screen_coords(mlx, sprs);
	calculate_spr_draw_bounds(sprs);
	if (sprs->drawStartY >= sprs->drawEndY || \
			sprs->drawStartX >= sprs->drawEndX)
		return ;
	current_grass_data = sprs->grass_data[spr->texture_index];
	stripe = sprs->drawStartX;
	while (stripe < sprs->drawEndX)
	{
		if (stripe >= 0 && stripe < screenWidth && \
				sprs->transformY > mlx->zbuffer[stripe])
		{
			stripe++;
			continue ;
		}
		render_spr_column(mlx, sprs, current_grass_data, stripe);
		stripe++;
	}
}

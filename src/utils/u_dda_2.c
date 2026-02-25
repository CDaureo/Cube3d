/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_dda_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:24:18 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/25 13:21:27 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_start(t_mlx *mlx, t_render *r)
{
	r->cameraX = 2 * r->x / (double)screenWidth - 1;
	r->rayDirX = mlx->dirX + mlx->planeX * r->cameraX;
	r->rayDirY = mlx->dirY + mlx->planeY * r->cameraX;
	r->mapX = (int)mlx->posX;
	r->mapY = (int)mlx->posY;
	if (r->rayDirY == 0)
		r->deltaDistY = 1e30;
	else
		r->deltaDistY = fabs(1 / r->rayDirY);
	if (r->rayDirX == 0)
		r->deltaDistX = 1e30;
	else
		r->deltaDistX = fabs(1 / r->rayDirX);
}

void	draw_ceiling_floor(t_mlx *mlx, t_color *colors, t_render *r)
{
	int	y;

	y = 0;
	while (y < r->drawStart)
	{
		ft_mlx_pixel_put(mlx, r->x, y, colors->ceiling_color);
		y++;
	}
	y = r->drawEnd + 1;
	while (y < screenHeight)
	{
		ft_mlx_pixel_put(mlx, r->x, y, colors->floor_color);
		y++;
	}
}

void	initialize_dda_step_x(t_mlx *mlx, t_render *r)
{
	if (r->rayDirX < 0)
	{
		r->stepX = -1;
		r->sideDistX = (mlx->posX - r->mapX) * r->deltaDistX;
	}
	else
	{
		r->stepX = 1;
		r->sideDistX = (r->mapX + 1.0 - mlx->posX) * r->deltaDistX;
	}
}

void	initialize_dda_step_y(t_mlx *mlx, t_render *r)
{
	if (r->rayDirY < 0)
	{
		r->stepY = -1;
		r->sideDistY = (mlx->posY - r->mapY) * r->deltaDistY;
	}
	else
	{
		r->stepY = 1;
		r->sideDistY = (r->mapY + 1.0 - mlx->posY) * r->deltaDistY;
	}
}

void	perform_dda_step(t_render *r)
{
	if (r->sideDistX < r->sideDistY)
	{
		r->sideDistX += r->deltaDistX;
		r->mapX += r->stepX;
		r->side = 0;
	}
	else
	{
		r->sideDistY += r->deltaDistY;
		r->mapY += r->stepY;
		r->side = 1;
	}
}

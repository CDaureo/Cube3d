/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_dda_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:24:18 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/25 16:32:58 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_start(t_mlx *mlx, t_render *r)
{
	r->camera_x = 2 * r->x / (double)screen_width - 1;
	r->raydir_x = mlx->dir_x + mlx->plane_x * r->camera_x;
	r->raydir_y = mlx->dir_y + mlx->plane_y * r->camera_x;
	r->map_x = (int)mlx->pos_x;
	r->map_y = (int)mlx->pos_y;
	if (r->raydir_y == 0)
		r->delta_dits_y = 1e30;
	else
		r->delta_dits_y = fabs(1 / r->raydir_y);
	if (r->raydir_x == 0)
		r->delta_dits_x = 1e30;
	else
		r->delta_dits_x = fabs(1 / r->raydir_x);
}

void	draw_ceiling_floor(t_mlx *mlx, t_color *colors, t_render *r)
{
	int	y;

	y = 0;
	while (y < r->draw_start)
	{
		ft_mlx_pixel_put(mlx, r->x, y, colors->ceiling_color);
		y++;
	}
	y = r->draw_end + 1;
	while (y < screen_height)
	{
		ft_mlx_pixel_put(mlx, r->x, y, colors->floor_color);
		y++;
	}
}

void	initialize_dda_step_x(t_mlx *mlx, t_render *r)
{
	if (r->raydir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (mlx->pos_x - r->map_x) * r->delta_dits_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - mlx->pos_x) * r->delta_dits_x;
	}
}

void	initialize_dda_step_y(t_mlx *mlx, t_render *r)
{
	if (r->raydir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (mlx->pos_y - r->map_y) * r->delta_dits_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - mlx->pos_y) * r->delta_dits_y;
	}
}

void	perform_dda_step(t_render *r)
{
	if (r->side_dist_x < r->side_dist_y)
	{
		r->side_dist_x += r->delta_dits_x;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->side_dist_y += r->delta_dits_y;
		r->map_y += r->step_y;
		r->side = 1;
	}
}

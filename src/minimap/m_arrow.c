/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_arrow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:17:22 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/18 14:42:47 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void draw_arrow_base_line(t_mlx *mlx, t_minimap *minimap, int i)
{
	minimap->lx3 = minimap->base_left_x + (int)((minimap->base_right_x - minimap->base_left_x) * i / 10.0);
	minimap->ly3 = minimap->base_left_y + (int)((minimap->base_right_y - minimap->base_left_y) * i / 10.0);
	minimap->outline_dx = minimap->lx3 - minimap->center_x;
	minimap->outline_dy = minimap->ly3 - minimap->center_y;
	
	if(minimap->outline_dx * minimap->outline_dx + minimap->outline_dy * minimap->outline_dy <= minimap->radius * minimap->radius)
	{
		if(minimap->lx3 >= 0 && minimap->ly3 >= 0 && minimap->lx3 < screenWidth && minimap->ly3 < screenHeight)
			ft_mlx_pixel_put(mlx, minimap->lx3, minimap->ly3, 0xFFFFFF);
	}
}

static void draw_arrow_side_lines(t_minimap *minimap, int i)
{
	minimap->lx1 = minimap->base_left_x + (int)((minimap->tip_x - minimap->base_left_x) * i / 20.0);
	minimap->ly1 = minimap->base_left_y + (int)((minimap->tip_y - minimap->base_left_y) * i / 20.0);
	minimap->lx2 = minimap->base_right_x + (int)((minimap->tip_x - minimap->base_right_x) * i / 20.0);
	minimap->ly2 = minimap->base_right_y + (int)((minimap->tip_y - minimap->base_right_y) * i / 20.0);
	minimap->outline_dx1 = minimap->lx1 - minimap->center_x;
	minimap->outline_dy1 = minimap->ly1 - minimap->center_y;
	minimap->outline_dx2 = minimap->lx2 - minimap->center_x;
	minimap->outline_dy2 = minimap->ly2 - minimap->center_y;
}

static void draw_left_arrow_side(t_mlx *mlx, t_minimap *minimap)
{
	if(minimap->outline_dx1 * minimap->outline_dx1 + minimap->outline_dy1 * minimap->outline_dy1 <= minimap->radius * minimap->radius)
	{
		if(minimap->lx1 >= 0 && minimap->ly1 >= 0 && minimap->lx1 < screenWidth && minimap->ly1 < screenHeight)
			ft_mlx_pixel_put(mlx, minimap->lx1, minimap->ly1, 0xFFFFFF);
	}
}

static void draw_right_arrow_side(t_mlx *mlx, t_minimap *minimap)
{
	if(minimap->outline_dx2 * minimap->outline_dx2 + minimap->outline_dy2 * minimap->outline_dy2 <= minimap->radius * minimap->radius)
	{
		if(minimap->lx2 >= 0 && minimap->ly2 >= 0 && minimap->lx2 < screenWidth && minimap->ly2 < screenHeight)
			ft_mlx_pixel_put(mlx, minimap->lx2, minimap->ly2, 0xFFFFFF);
	}
}

void draw_arrow_outline(t_mlx *mlx, t_minimap *minimap)
{
	int i;

	i = 0;
	calculate_arrow_points(minimap);
	while(i <= 20)
	{
		draw_arrow_side_lines(minimap, i);
		if(i <= 10)
			draw_arrow_base_line(mlx, minimap, i);
		draw_left_arrow_side(mlx, minimap);
		draw_right_arrow_side(mlx, minimap);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_arrow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:41:45 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/18 14:41:54 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void draw_arrow_body(t_mlx *mlx, t_minimap *minimap)
{
	minimap->scan_y = -minimap->arrow_length;
	
	while(minimap->scan_y <= minimap->arrow_length)
	{
		if(minimap->scan_y < 0)
			minimap->width_at_y = (minimap->arrow_width * (minimap->arrow_length + minimap->scan_y)) / minimap->arrow_length;
		else
			minimap->width_at_y = minimap->arrow_width;
		minimap->dx = -minimap->width_at_y;
		while(minimap->dx <= minimap->width_at_y)
		{   
			minimap->current_x = minimap->player_pixel_x + minimap->dx;
			minimap->current_y_adj = minimap->player_pixel_y + minimap->scan_y;
			minimap->arrow_dx = minimap->current_x - minimap->center_x;
			minimap->arrow_dy = minimap->current_y_adj - minimap->center_y;
			
			if(minimap->arrow_dx * minimap->arrow_dx + minimap->arrow_dy * minimap->arrow_dy <= minimap->radius * minimap->radius)
			{
				if(minimap->current_x >= 0 && minimap->current_y_adj >= 0 && minimap->current_x < screenWidth && minimap->current_y_adj < screenHeight)
					ft_mlx_pixel_put(mlx, minimap->current_x, minimap->current_y_adj, 0xFF0000);
			}
			minimap->dx++;
		}
		minimap->scan_y++;
	}
}

void calculate_arrow_points(t_minimap *minimap)
{
	minimap->tip_x = minimap->player_pixel_x;
	minimap->tip_y = minimap->player_pixel_y - minimap->arrow_length;
	minimap->base_center_x = minimap->player_pixel_x;
	minimap->base_center_y = minimap->player_pixel_y + minimap->arrow_length;
	minimap->base_left_x = minimap->base_center_x - minimap->arrow_width;
	minimap->base_left_y = minimap->base_center_y;
	minimap->base_right_x = minimap->base_center_x + minimap->arrow_width;
	minimap->base_right_y = minimap->base_center_y;
}

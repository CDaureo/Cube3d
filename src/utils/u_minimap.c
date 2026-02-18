/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_minimap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:02:01 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/18 17:02:26 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void init_minimap(t_minimap *minimap, t_mlx *mlx)
{
	minimap->map_start_x = screenWidth - MINIMAP_SIZE - MINIMAP_OFFSET;
	minimap->map_start_y = screenHeight - MINIMAP_SIZE - MINIMAP_OFFSET;
	minimap->center_x = minimap->map_start_x + MINIMAP_SIZE / 2;
	minimap->center_y = minimap->map_start_y + MINIMAP_SIZE / 2;
	minimap->radius = MINIMAP_SIZE / 2;
	minimap->player_pixel_x = minimap->center_x;
	minimap->player_pixel_y = minimap->center_y;
	minimap->player_angle = atan2(mlx->dirY, mlx->dirX) + M_PI/2;  // Was - M_PI/2
	minimap->arrow_length = 6;
	minimap->arrow_width = 4;
}

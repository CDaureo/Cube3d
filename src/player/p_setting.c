/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_setting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:50:18 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/19 13:51:14 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void set_north_direction(t_mlx *mlx, double plane_length)
{
	mlx->dirX = 0;
	mlx->dirY = -1;
	mlx->planeX = plane_length;
	mlx->planeY = 0;
}

static void set_south_direction(t_mlx *mlx, double plane_length)
{
	mlx->dirX = 0;
	mlx->dirY = 1;
	mlx->planeX = -plane_length;
	mlx->planeY = 0;
}

static void set_east_direction(t_mlx *mlx, double plane_length)
{
	mlx->dirX = 1;
	mlx->dirY = 0;
	mlx->planeX = 0;
	mlx->planeY = plane_length;
}

static void set_west_direction(t_mlx *mlx, double plane_length)
{
	mlx->dirX = -1;
	mlx->dirY = 0;
	mlx->planeX = 0;
	mlx->planeY = -plane_length;
}

void set_player_direction(t_mlx *mlx, char player_dir, double plane_length)
{
	if (player_dir == 'N')
		set_north_direction(mlx, plane_length);
	else if (player_dir == 'S')
		set_south_direction(mlx, plane_length);
	else if (player_dir == 'E')
		set_east_direction(mlx, plane_length);
	else if (player_dir == 'W')
		set_west_direction(mlx, plane_length);
	else
		set_west_direction(mlx, plane_length);
}

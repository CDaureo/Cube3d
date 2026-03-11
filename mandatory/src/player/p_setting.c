/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_setting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:50:18 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/25 13:39:27 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_north_direction(t_mlx *mlx, double plane_length)
{
	mlx->dir_x = 0;
	mlx->dir_y = -1;
	mlx->plane_x = plane_length;
	mlx->plane_y = 0;
}

static void	set_south_direction(t_mlx *mlx, double plane_length)
{
	mlx->dir_x = 0;
	mlx->dir_y = 1;
	mlx->plane_x = -plane_length;
	mlx->plane_y = 0;
}

static void	set_east_direction(t_mlx *mlx, double plane_length)
{
	mlx->dir_x = 1;
	mlx->dir_y = 0;
	mlx->plane_x = 0;
	mlx->plane_y = plane_length;
}

static void	set_west_direction(t_mlx *mlx, double plane_length)
{
	mlx->dir_x = -1;
	mlx->dir_y = 0;
	mlx->plane_x = 0;
	mlx->plane_y = -plane_length;
}

void	set_player_direction(t_mlx *mlx, char player_dir, double plane_length)
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

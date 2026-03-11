/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_mouse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:47:41 by simgarci          #+#    #+#             */
/*   Updated: 2026/03/11 17:49:01 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate_right(t_mlx *mlx)
{
	double	rotation_speed;
	double	olddir_x;
	double	oldplane_x;

	rotation_speed = 0.05;
	olddir_x = mlx->dir_x;
	mlx->dir_x = mlx->dir_x * cos(-rotation_speed) - \
		mlx->dir_y * sin(-rotation_speed);
	mlx->dir_y = olddir_x * sin(-rotation_speed) + \
		mlx->dir_y * cos(-rotation_speed);
	oldplane_x = mlx->plane_x;
	mlx->plane_x = mlx->plane_x * cos(-rotation_speed) - \
		mlx->plane_y * sin(-rotation_speed);
	mlx->plane_y = oldplane_x * sin(-rotation_speed) + \
		mlx->plane_y * cos(-rotation_speed);
}

void	rotate_left(t_mlx *mlx)
{
	double	rotation_speed;
	double	olddir_x;
	double	oldplane_x;

	rotation_speed = 0.05;
	olddir_x = mlx->dir_x;
	mlx->dir_x = mlx->dir_x * cos(rotation_speed) - \
		mlx->dir_y * sin(rotation_speed);
	mlx->dir_y = olddir_x * sin(rotation_speed) + \
		mlx->dir_y * cos(rotation_speed);
	oldplane_x = mlx->plane_x;
	mlx->plane_x = mlx->plane_x * cos(rotation_speed) - \
		mlx->plane_y * sin(rotation_speed);
	mlx->plane_y = oldplane_x * sin(rotation_speed) + \
		mlx->plane_y * cos(rotation_speed);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_mouse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:36:26 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/18 14:14:28 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void mouse_rotation(t_mouse *mouse, t_mlx *mlx)
{
	if (abs(mouse->delta_x) > 1 || abs(mouse->delta_y) > 1)
	{
		if (abs(mouse->delta_x) > 1)
		{
			mouse->rotation = mouse->delta_x * MOUSE_SENS_X * 0.5;
			mouse->oldDirX = mlx->dirX;
			mlx->dirX = mlx->dirX * cos(mouse->rotation) - mlx->dirY * sin(mouse->rotation);
			mlx->dirY = mouse->oldDirX * sin(mouse->rotation) + mlx->dirY * cos(mouse->rotation);
			mouse->oldPlaneX = mlx->planeX;
			mlx->planeX = mlx->planeX * cos(mouse->rotation) - mlx->planeY * sin(mouse->rotation);
			mlx->planeY = mouse->oldPlaneX * sin(mouse->rotation) + mlx->planeY * cos(mouse->rotation);
		}
		if (abs(mouse->delta_y) > 1)
		{
			mlx->pitch += (-mouse->delta_y) * MOUSE_SENS_Y * 0.5;
			if (mlx->pitch < -320) mlx->pitch = -320;
			if (mlx->pitch > 320) mlx->pitch = 320;
		}
		mlx_mouse_move(mlx->mlx, mlx->win, mouse->center_x, mouse->center_y);
	}
}

int handle_mouse_move(int x, int y, t_mlx *mlx)
{
	t_mouse mouse;
	
	mouse.center_x = screenWidth / 2;
	mouse.center_y = screenHeight / 2;
	mouse.delta_x = x - mouse.center_x;
	mouse.delta_y = y - mouse.center_y;
	if (!mlx->mouse_locked)
		return (0);
	mouse_rotation(&mouse, mlx);
	return (0);
	}

int handle_mouse_press(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;

	if (button == 1)
	{
		if (!mlx->mouse_locked)
		{
			mlx->mouse_locked = 1;
			mlx->last_mouse_x = screenWidth / 2;
			mlx->last_mouse_y = screenHeight / 2;
			mlx_mouse_hide(mlx->mlx, mlx->win);
			mlx_mouse_move(mlx->mlx, mlx->win, mlx->last_mouse_x, mlx->last_mouse_y);
		}
	}
	return (0);
}
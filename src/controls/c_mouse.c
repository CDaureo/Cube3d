/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_mouse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:36:26 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/22 19:25:10 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	change_rotation(t_mouse *m, t_mlx *mlx)
{
	m->rotation = m->delta_x * MOUSE_SENS_X * 0.5;
	m->oldDirX = mlx->dirX;
	mlx->dirX = mlx->dirX * cos(m->rotation) \
		- mlx->dirY * sin(m->rotation);
	mlx->dirY = m->oldDirX * sin(m->rotation) \
		+ mlx->dirY * cos(m->rotation);
	m->oldPlaneX = mlx->planeX;
	mlx->planeX = mlx->planeX * cos(m->rotation) \
		- mlx->planeY * sin(m->rotation);
	mlx->planeY = m->oldPlaneX * sin(m->rotation) \
		+ mlx->planeY * cos(m->rotation);
}

void	mouse_rotation(t_mouse *m, t_mlx *mlx)
{
	if (abs(m->delta_x) > 1 || abs(m->delta_y) > 1)
	{
		if (abs(m->delta_x) > 1)
			change_rotation(m, mlx);
		if (abs(m->delta_y) > 1)
		{
			mlx->pitch += (-m->delta_y) * MOUSE_SENS_Y * 0.5;
			if (mlx->pitch < -320)
				mlx->pitch = -320;
			if (mlx->pitch > 320)
				mlx->pitch = 320;
		}
		mlx_mouse_move(mlx->mlx, mlx->win, m->center_x, m->center_y);
	}
}

int	handle_mouse_move(int x, int y, t_mlx *mlx)
{
	t_mouse	mouse;

	mouse.center_x = screenWidth / 2;
	mouse.center_y = screenHeight / 2;
	mouse.delta_x = x - mouse.center_x;
	mouse.delta_y = y - mouse.center_y;
	if (!mlx->mouse_locked)
		return (0);
	mouse_rotation(&mouse, mlx);
	return (0);
}

int	handle_mouse_press(int button, int x, int y, t_mlx *mlx)
{
	(void) x;
	(void) y;
	if (button == 1)
	{
		if (!mlx->mouse_locked)
		{
			mlx->mouse_locked = 1;
			mlx->last_mouse_x = screenWidth / 2;
			mlx->last_mouse_y = screenHeight / 2;
			mlx_mouse_hide(mlx->mlx, mlx->win);
			mlx_mouse_move(mlx->mlx, mlx->win, \
				mlx->last_mouse_x, mlx->last_mouse_y);
		}
	}
	return (0);
}

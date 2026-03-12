/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_mouse_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:36:26 by simgarci          #+#    #+#             */
/*   Updated: 2026/03/12 13:26:34 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	change_rotation(t_mouse *m, t_mlx *mlx)
{
	m->rotation = m->delta_x * MOUSE_SENS_X * 0.5;
	m->olddir_x = mlx->dir_x;
	mlx->dir_x = mlx->dir_x * cos(m->rotation) \
		- mlx->dir_y * sin(m->rotation);
	mlx->dir_y = m->olddir_x * sin(m->rotation) \
		+ mlx->dir_y * cos(m->rotation);
	m->oldplane_x = mlx->plane_x;
	mlx->plane_x = mlx->plane_x * cos(m->rotation) \
		- mlx->plane_y * sin(m->rotation);
	mlx->plane_y = m->oldplane_x * sin(m->rotation) \
		+ mlx->plane_y * cos(m->rotation);
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

	mouse.center_x = SCREEN_WIDTH / 2;
	mouse.center_y = SCREEN_HEIGHT / 2;
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
			mlx->last_mouse_x = SCREEN_WIDTH / 2;
			mlx->last_mouse_y = SCREEN_HEIGHT / 2;
			mlx_mouse_hide(mlx->mlx, mlx->win);
			mlx_mouse_move(mlx->mlx, mlx->win, \
				mlx->last_mouse_x, mlx->last_mouse_y);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_movement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:03:00 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/25 17:52:24 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	get_movement_speed(t_mlx *mlx)
{
	if (mlx->key_state[4])
		return (MOVE_SPEED * 2.0);
	else
		return (MOVE_SPEED);
}

int	handle_vertical_movement(t_mlx *mlx, t_map *map, t_game *game)
{
	double	current_speed;

	current_speed = get_movement_speed(mlx);
	if (mlx->key_state[0])
	{
		if (get_map_value(map, (int)(mlx->pos_x + mlx->dir_x * current_speed), \
			(int)(mlx->pos_y), game) == 0)
			mlx->pos_x += mlx->dir_x * current_speed;
		if (get_map_value(map, (int)(mlx->pos_x), \
			(int)(mlx->pos_y + mlx->dir_y * current_speed), game) == 0)
			mlx->pos_y += mlx->dir_y * current_speed;
	}
	if (mlx->key_state[2])
	{
		if (get_map_value(map, (int)(mlx->pos_x - mlx->dir_x * current_speed), \
			(int)(mlx->pos_y), game) == 0)
			mlx->pos_x -= mlx->dir_x * current_speed;
		if (get_map_value(map, (int)(mlx->pos_x), \
			(int)(mlx->pos_y - mlx->dir_y * current_speed), game) == 0)
			mlx->pos_y -= mlx->dir_y * current_speed;
	}
	return (0);
}

int	handle_horizontal_movement(t_mlx *mlx, t_map *map, t_game *game)
{
	double	current_speed;

	current_speed = get_movement_speed(mlx);
	if (mlx->key_state[1])
	{
		if (get_map_value(map, (int)(mlx->pos_x - \
				mlx->plane_x * current_speed), (int)(mlx->pos_y), game) == 0)
			mlx->pos_x -= mlx->plane_x * current_speed;
		if (get_map_value(map, (int)(mlx->pos_x), \
			(int)(mlx->pos_y - mlx->plane_y * current_speed), game) == 0)
			mlx->pos_y -= mlx->plane_y * current_speed;
	}
	if (mlx->key_state[3])
	{
		if (get_map_value(map, (int)(mlx->pos_x + mlx->plane_x * \
				current_speed), (int)(mlx->pos_y), game) == 0)
			mlx->pos_x += mlx->plane_x * current_speed;
		if (get_map_value(map, (int)(mlx->pos_x), \
			(int)(mlx->pos_y + mlx->plane_y * current_speed), game) == 0)
			mlx->pos_y += mlx->plane_y * current_speed;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_movement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:03:00 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/18 17:03:36 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double get_movement_speed(t_mlx *mlx)
{
	if (mlx->key_state[4])
		return MOVE_SPEED * 2.0;
	else
		return MOVE_SPEED;
}

int handle_vertical_movement(t_mlx *mlx, t_map *map, t_game *game)
{
	double current_speed;
	
	current_speed = get_movement_speed(mlx);
	if (mlx->key_state[0])
	{
		if(get_map_value(map, (int)(mlx->posX + mlx->dirX * current_speed), (int)(mlx->posY), game) == 0) 
			mlx->posX += mlx->dirX * current_speed;
		if(get_map_value(map, (int)(mlx->posX), (int)(mlx->posY + mlx->dirY * current_speed), game) == 0) 
			mlx->posY += mlx->dirY * current_speed;
	}
	if (mlx->key_state[2])
	{
		if(get_map_value(map, (int)(mlx->posX - mlx->dirX * current_speed), (int)(mlx->posY), game) == 0) 
			mlx->posX -= mlx->dirX * current_speed;
		if(get_map_value(map, (int)(mlx->posX), (int)(mlx->posY - mlx->dirY * current_speed), game) == 0) 
			mlx->posY -= mlx->dirY * current_speed;
	}
	return (0);
}

int handle_horizontal_movement(t_mlx *mlx, t_map *map, t_game *game)
{
	double current_speed;
	
	current_speed = get_movement_speed(mlx);
	if (mlx->key_state[1])
	{
		if(get_map_value(map, (int)(mlx->posX - mlx->planeX * current_speed), (int)(mlx->posY), game) == 0) 
		mlx->posX -= mlx->planeX * current_speed;
		if(get_map_value(map, (int)(mlx->posX), (int)(mlx->posY - mlx->planeY * current_speed), game) == 0) 
		mlx->posY -= mlx->planeY * current_speed;
	}
	if (mlx->key_state[3])
	{
		if(get_map_value(map, (int)(mlx->posX + mlx->planeX * current_speed), (int)(mlx->posY), game) == 0) 
			mlx->posX += mlx->planeX * current_speed;
		if(get_map_value(map, (int)(mlx->posX), (int)(mlx->posY + mlx->planeY * current_speed), game) == 0) 
			mlx->posY += mlx->planeY * current_speed;
		}
	return (0);
}

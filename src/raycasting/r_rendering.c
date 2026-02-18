/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_rendering.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:21:49 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/18 17:22:07 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void render_scene(t_game *game)
{
	t_render r;
	t_mlx *mlx;
	t_map *map;

	map = &game->maps;
	mlx = &game->mlx;
	r.x = 0;
	clear_image(mlx);
	while(r.x < screenWidth)
	{
		render_start(mlx, &r);	 
		apply_dda(mlx, &r, map, game);
		data_update(mlx, &r, game);
		draw_ceiling_floor(mlx, &game->colors, r.x, r.drawStart, r.drawEnd);
		vertical_update(mlx, &r, game);
		mlx->zbuffer[r.x] = r.perpWallDist;
		
		r.x++;
	}
	render_sprites(mlx, &game->sprites);
	draw_minimap(mlx, map, game);
	draw_crosshair(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int render_loop(t_game *game)
{
	static int frame_count;
	t_mlx *mlx;
	t_map *map;
	
	frame_count = 0;
	mlx = &game->mlx;
	map = &game->maps;
	frame_count++;
	handle_vertical_movement(mlx, map, game);
	handle_horizontal_movement(mlx, map, game);
	render_scene(game);
	
	return (0);
}

void initialize_mlx(t_mlx *mlx)
{
	int i;
	
	i = 0;
	while (i < 10)
	{
		mlx->key_state[i] = 0;
		i++;
	}
	mlx->pitch = 0;
	mlx->last_mouse_x = screenWidth / 2;
	mlx->last_mouse_y = screenHeight / 2;
	mlx->mouse_locked = 0;
	mlx->needs_render = 1;
	mlx->last_render_time = 0;
	mlx->zbuffer = malloc(sizeof(double) * screenWidth);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, screenWidth, screenHeight, "Cub3D Raycasting");
	mlx->img = mlx_new_image(mlx->mlx, screenWidth, screenHeight);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
}

int render_loop_wrapper(void *param)
{
	return render_loop((t_game *)param);
}

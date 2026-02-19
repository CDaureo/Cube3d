/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:07:55 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/02/19 13:53:38 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
	t_game game;
	t_minimap minimap;

	if(error_checker(&game, argc, argv))
		return (1);
	initialize_player_from_map(&game.mlx, &game.maps);
	load_grass_texture(&game);
	generate_grass_sprites(&game, &minimap);
	mlx_hook(game.mlx.win, 2, 1L << 0, handle_keys, &game);
	mlx_hook(game.mlx.win, 3, 1L << 1, handle_key_release, &game);
	mlx_hook(game.mlx.win, 4, 1L << 2, handle_mouse_press, &game.mlx);
	mlx_hook(game.mlx.win, 6, 1L << 6, handle_mouse_move, &game.mlx);
	mlx_hook(game.mlx.win, 17, 0, close_hook, &game.mlx);
	mlx_loop_hook(game.mlx.mlx, render_loop_wrapper, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}

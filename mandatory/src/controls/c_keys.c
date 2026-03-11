/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_keys.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:09:21 by simgarci          #+#    #+#             */
/*   Updated: 2026/03/11 17:49:16 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	check_keycodes(t_mlx *mlx, int keycode, t_game *game)
{
	if (keycode == KEY_W)
		mlx->key_state[0] = 1;
	if (keycode == KEY_A)
		mlx->key_state[1] = 1;
	if (keycode == KEY_S)
		mlx->key_state[2] = 1;
	if (keycode == KEY_D)
		mlx->key_state[3] = 1;
	if (keycode == KEY_SHIFT)
		mlx->key_state[4] = 1;
	if (keycode == KEY_RIGHT)
		mlx->key_state[5] = 1;
	if (keycode == KEY_LEFT)
		mlx->key_state[6] = 1;
	if (keycode == KEY_INTERACT)
		interact_with_door(game);
}

int	handle_keys(int keycode, t_game *game)
{
	t_mlx	*mlx;

	mlx = &game->mlx;
	if (keycode == 65307)
	{
		if (mlx->mouse_locked)
		{
			mlx->mouse_locked = 0;
			mlx_mouse_show(mlx->mlx, mlx->win);
			printf("Mouse unlocked\n");
			return (0);
		}
		exit(0);
	}
	check_keycodes(mlx, keycode, game);
	return (0);
}

int	handle_key_release(int keycode, t_game *game)
{
	t_mlx	*mlx;

	mlx = &game->mlx;
	if (keycode == KEY_W)
		mlx->key_state[0] = 0;
	if (keycode == KEY_A)
		mlx->key_state[1] = 0;
	if (keycode == KEY_S)
		mlx->key_state[2] = 0;
	if (keycode == KEY_D)
		mlx->key_state[3] = 0;
	if (keycode == KEY_SHIFT)
		mlx->key_state[4] = 0;
	if (keycode == KEY_RIGHT)
		mlx->key_state[5] = 0;
	if (keycode == KEY_LEFT)
		mlx->key_state[6] = 0;
	return (0);
}

void	process_continuous_input(t_game *game)
{
	if (game->mlx.key_state[0] || game->mlx.key_state[2])
		handle_vertical_movement(&game->mlx, &game->maps, game);
	if (game->mlx.key_state[1] || game->mlx.key_state[3])
		handle_horizontal_movement(&game->mlx, &game->maps, game);
	if (game->mlx.key_state[5])
		rotate_left(&game->mlx);
	if (game->mlx.key_state[6])
		rotate_right(&game->mlx);
}

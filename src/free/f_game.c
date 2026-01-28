/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_game.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:06:55 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/01/24 21:14:52 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void cleanup_game(t_game *game)
{
	free_mlx(game);

	free_map(&game->maps);
	free_textures(game);
}
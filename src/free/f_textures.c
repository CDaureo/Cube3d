/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_textures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:11:52 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/02/23 16:38:35 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/* Libera las rutas de texturas */
void	free_textures(t_game *game)
{
	if (game->textures.north)
		free(game->textures.north);
	if (game->textures.south)
		free(game->textures.south);
	if (game->textures.west)
		free(game->textures.west);
	if (game->textures.east)
		free(game->textures.east);
	if (game->textures.door)
		free(game->textures.door);	
}

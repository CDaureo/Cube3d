/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_textures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:11:52 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/02/25 12:47:20 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/* Libera las rutas de texturas */
void	free_textures(t_game *game)
{
	if (game->txt.north)
		free(game->txt.north);
	if (game->txt.south)
		free(game->txt.south);
	if (game->txt.west)
		free(game->txt.west);
	if (game->txt.east)
		free(game->txt.east);
	if (game->txt.door)
		free(game->txt.door);	
}

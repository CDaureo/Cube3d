/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:13:58 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/25 12:40:25 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validator(t_game *game)
{
	if (!validate_texture_file(game->textures.north)
		|| !validate_texture_file(game->textures.south)
		|| !validate_texture_file(game->textures.west)
		|| !validate_texture_file(game->textures.east)
		|| !validate_texture_file(game->textures.door))
		return (0);
	return (1);
}

int	parse_error_checker(int ret, t_game *game )
{
	if (!ret)
		return (printf("Error:\nInvalid .cub file (parse_line)\n"), 0);
	if (game->maps.height == 0)
		return (printf("Error:\nNo map block found\n"), 0);
	if (!finalize_map(&game->maps))
		return (printf("Error:\nfinalize_map failed\n"), 0);
	if (!validate_map_basic(&game->maps))
		return (printf("Error:\nvalidate_map_basic failed\n"), 0);
	if (!validate_map_closed(&game->maps))
		return (printf("Error:\nMap is not closed by walls\n"), 0);
	if (!game->textures.north || !game->textures.south
		|| !game->textures.west || !game->textures.east || !game->textures.door)
		return (printf("Error:\nMissing textures\n"), 0);
	if (!game->colors.floor_set || !game->colors.ceiling_set)
		return (printf("Error:\nMissing colors F/C\n"), 0);
	return (1);
}

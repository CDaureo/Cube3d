/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:13:58 by simgarci          #+#    #+#             */
/*   Updated: 2026/03/12 13:26:34 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validator(t_game *game)
{
	if (!validate_texture_file(game->txt.north)
		|| !validate_texture_file(game->txt.south)
		|| !validate_texture_file(game->txt.west)
		|| !validate_texture_file(game->txt.east)
		|| !validate_texture_file(game->txt.door))
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
	if (!game->txt.north || !game->txt.south || \
		!game->txt.west || !game->txt.east || !game->txt.door)
		return (printf("Error:\nMissing textures\n"), 0);
	if (!game->colors.floor_set || !game->colors.ceiling_set)
		return (printf("Error:\nMissing colors F/C\n"), 0);
	return (1);
}

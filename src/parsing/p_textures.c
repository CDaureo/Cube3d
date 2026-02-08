/* ************************************************************************** */
/*																		    */
/*												        :::      ::::::::   */
/*   parser.c									      :+:      :+:    :+:   */
/*												    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*												+#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:43:09 by cdaureo-          #+#    #+#			 */
/*   Updated: 2026/01/19 14:07:24 by cdaureo-         ###   ########.fr       */
/*																		    */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Procesa una línea de textura (NO, SO, WE, EA) */

int	parse_texture_line(char *line, t_game *game)
{
	char *path;
	char *trim;

	trim = trim_whitespace(line);
	if (ft_strncmp(trim,"NO ", 3) == 0)
	{
		path = trim_whitespace(trim + 3);
		game->textures.north = ft_strdup(path);
		        printf("DEBUG: Parsed north texture: '%s' (length: %zu)\n", 
               game->textures.north, strlen(game->textures.north));
	}
	else if (ft_strncmp(trim,"SO ", 3) == 0)
	{
		path = trim_whitespace(trim + 3);
		game->textures.south = ft_strdup(path);
	}
	else if (ft_strncmp(trim,"WE ", 3) == 0)
	{
		path = trim_whitespace(trim + 3);
		game->textures.west = ft_strdup(path);
	}
	else if (ft_strncmp(trim,"EA ", 3) == 0)
	{
		path = trim_whitespace(trim + 3);
		game->textures.east = ft_strdup(path);
	}
	return(1);
}

/* Lee el archivo .cub y extrae las rutas de texturas */
int parse_textures(int fd, t_game *game)
{
	char *line;
	int counter;

	counter = 0;
	while (counter < 4 && (line = get_next_line(fd)))
	{
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		{
			parse_texture_line(line, game);
			counter++;
		}
		free(line);
	}
	if (counter != 4)
		return(printf("Error:\nMissing texture definitions\n"), 0);
	if (!validate_texture_file(game->textures.north)
	|| !validate_texture_file(game->textures.south)
	|| !validate_texture_file(game->textures.west)
	|| !validate_texture_file(game->textures.east))
		return(0);
	return(1);
}


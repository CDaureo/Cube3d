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
	else if (ft_strncmp(trim,"DO ", 3) == 0)
	{
		path = trim_whitespace(trim + 3);
		game->textures.door = ft_strdup(path);
	}
	return(1);
	return(1);
}

/* Lee el archivo .cub y extrae las rutas de texturas */
int parse_textures(int fd, t_game *game)
{
    char *line;
    int counter;

    counter = 0;
    while (counter < 5 && (line = get_next_line(fd)))  // Changed from 4 to 5
    {
        if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
            || ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
            || ft_strncmp(line, "DO ", 3) == 0)  // Add DO check
        {
            parse_texture_line(line, game);
            counter++;
        }
        free(line);
    }
    if (counter != 5)  // Changed from 4 to 5
        return(printf("Error:\nMissing texture definitions\n"), 0);
    if (!validate_texture_file(game->textures.north)
    || !validate_texture_file(game->textures.south)
    || !validate_texture_file(game->textures.west)
    || !validate_texture_file(game->textures.east)
    || !validate_texture_file(game->textures.door))  // Add door validation
        return(0);
    return(1);
}


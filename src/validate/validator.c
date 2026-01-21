/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:14:57 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/01/21 14:15:08 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*File Validator*/
int validate_extension(const char *file)
{
	size_t len;

	len = ft_strlen(file);
	if (!file)
		return (0);
	if (len < 4)
		return (0);
	if (ft_strcmp(file + len - 4, ".cub") == 0)
		return(1);
	return(0);	
}
/* Valida que el archivo de textura exista y sea accesible */
int	validate_texture_file(const char *path)
{
	int fd;
	if (!path)
		return(0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return(printf("Error:\nTexture file not accesible; %s\n",path));
	close(fd);
	return(1);
}

int validate_map_basic(t_map *map)
{
	int players;
	int x;
	int y;
	char c;

	players = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			c = map->rows[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				players++;
				map->player_x = x;
				map->player_y = y;
				map->player_dir = c;
			}
			x++;
		}
		y++;
	}
	if (players == 0)
		return (printf("Error\nNo se encontró posición inicial del jugador\n"), 0);
	if (players > 1)
		return (printf("Error\nMúltiples posiciones de jugador encontradas\n"), 0);
	return 1;
}
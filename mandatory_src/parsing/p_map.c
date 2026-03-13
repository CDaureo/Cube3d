/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:08:09 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/03/13 15:47:41 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_map_line(char *line, t_map *map)
{
	char	*row;
	size_t	len;

	if (!line)
		return (0);
	row = ft_strdup(line);
	if (!row)
		return (printf("Error: Not enough memory dupping map row"), 0);
	len = ft_strlen(row);
	if (len > 0 && (row[len - 1] == '\n' || row[len - 1] == '\r'))
		row[len - 1] = '\0';
	if (!sanitize_row(row))
		return (free(row), \
		printf("No valid character on map (sanitize): \"%s\"\n", row), 0);
	return (push_row(map, row));
}

int	finalize_map(t_map *map)
{
	int		i;
	int		len;
	char	*padded;

	i = 0;
	len = 0;
	while (i < map->height)
	{
		len = (int)ft_strlen(map->rows[i]);
		if (len < map->width)
		{
			padded = (char *)malloc(map->width + 1);
			if (!padded)
				return (printf("Error: Not enough memory normalize map"), 0);
			ft_memcpy(padded, map->rows[i], len);
			ft_memset(padded + len, ' ', map->width - len);
			padded[map->width] = '\0';
			free(map->rows[i]);
			map->rows[i] = padded;
		}
		i++;
	}
	return (1);
}

/* Comprueba si el carácter es un tile "abierto" que requiere estar cerrado por paredes */
static int	is_playable_tile(char c)
{
    if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D')
        return (1);
    return (0);
}

/* Valida que el mapa esté cerrado: ningún tile jugable en borde ni con espacio adyacente */
int	is_map_closed(t_map *map)
{
    int	y;
    int	x;
    char	c;

    if (!map || map->height <= 0 || map->width <= 0)
        return (printf("Error: map vacío o inválido\n"), 0);
    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            c = map->rows[y][x];
            if (is_playable_tile(c))
            {
                /* si está en el borde, no está cerrado */
                if (y == 0 || x == 0 || y == map->height - 1 || x == map->width - 1)
                    return (printf("Error: mapa no cerrado (tile en borde) en %d,%d\n", y, x), 0);
                /* vecinos up/down/left/right no deben ser espacio ' ' ni fin de cadena */
                if (map->rows[y - 1][x] == ' ' || map->rows[y + 1][x] == ' '
                    || map->rows[y][x - 1] == ' ' || map->rows[y][x + 1] == ' ')
                    return (printf("Error: mapa no cerrado (espacio adyacente) en %d,%d\n", y, x), 0);
            }
            x++;
        }
        y++;
    }
    return (1);
}

int	parse_map(int fd, t_game *game)
{
    char	*line;
    char	*trim;
    int		started;

    started = 0;
    while ((line = get_next_line(fd)))
    {
        trim = trim_whitespace(line);
        /* línea vacía */
        if (trim[0] == '\0')
        {
            free(line);
            if (started)
                break; /* mapa terminado por línea en blanco */
            else
                continue; /* seguir buscando inicio de mapa */
        }
        /* si la línea no es una fila de mapa válida */
        if (!sanitize_row(trim))
        {
            free(line);
            if (started)
                return (printf("Error: línea inválida dentro del mapa: \"%s\"\n", trim), 0);
            else
                return (printf("Error: línea inválida antes del mapa: \"%s\"\n", trim), 0);
        }
        /* procesar fila de mapa */
        if (!parse_map_line(line, &game->maps))
        {
            free(line);
            return (0);
        }
        free(line);
        started = 1;
    }
    if (!started)
        return (printf("Error: no se encontró ninguna fila de mapa\n"), 0);
    /* normalizar y validar cierre */
    if (!finalize_map(&game->maps) || !is_map_closed(&game->maps))
        return (printf("Failed to parse map\n"), 0);
    return (1);
}
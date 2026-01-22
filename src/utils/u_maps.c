/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_maps.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:15:39 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/01/22 13:39:35 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * Valida si un carácter es permitido en el mapa
 * Caracteres válidos: '0', '1', ' ', '\t', 'N', 'S', 'E', 'W'
 */
int is_allow_chars(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == '\t' ||
			c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
/**
 * Valida que todos los caracteres de una línea de mapa sean permitidos
 * Ignora saltos de línea (\n, \r)
 * Retorna 1 si válida, 0 si contiene caracteres no permitidos
 */
int sanitize_row(const char *row)
{
	int i;

	i = 0;
	if (!row)
		return(0);
	
	while (row[i])
	{
		if (row[i] == '\n' || row[i] == '\r')
		{
			i++;
			continue;
		}
		if (is_allow_chars(row[i]))
			return(0);
		i++;
	}
	return (1);
}
/**
 * Añade una nueva fila al mapa y expande el array dinámicamente
 * Actualiza la altura y el ancho máximo del mapa
 */
int push_row(t_map *map, char *row_dup)
{
	char	**new_row;
	int		i;
	
	i = 0;
	new_row = (char **)malloc(sizeof(char *) * (map->height + 2));
	if (!new_row)
		return(printf("Error: Not enought memory.\n"));
	while (i < map->height)
	{
		new_row[i] = map->rows[i];
			i++;
	}
	new_row[i++] = row_dup;
	new_row[i] = NULL;
	free(map->rows);
	map->rows = new_row;
	map->height += 1;
	if ((int)ft_strlen(row_dup) > map->width)
		map->width = (int)ft_strlen(row_dup);
	return (1);
}
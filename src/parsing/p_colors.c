/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_colors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:29:25 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/01/24 20:35:47 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * Valida y convierte una cadena RGB a un entero de color
 * Formato esperado: "R,G,B" donde R, G, B están entre 0-255
 */
int parse_rgb(char *rgb_str, t_color *data)
{
	int	red;
	int	green;
	int	blue;
	char	**parts;
	(void)data;
	
	if (!rgb_str || !*rgb_str)
		return(printf("Invalid RGB color: Empty string\n"), -1);
	parts = ft_split(rgb_str,',');
	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
		return(ft_free_split(parts), printf("Invalid RGB Format: Must be 'R,G,B'\n"), -1);
	red = ft_atoi(parts[0]);
	green = ft_atoi(parts[1]);
	blue = ft_atoi(parts[2]);

	if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
		return(ft_free_split(parts), printf("GB values out of range [0-255]\n "), -1);

	ft_free_split(parts);
	return((red << 16) | (green << 8) | blue);
	
}
/**
 * Parsea la línea de color del suelo (F)
 */
int parse_floor_color(char *line, t_color *data)
{
	char	*rgb_str;
	int		color;

	rgb_str = ft_strtrim(line + 1, " \t");
	if (!rgb_str)
		return(printf("Memory error parsing floor color\n"), -1);
	color = parse_rgb(rgb_str,data);
	free(rgb_str);
	if (color == -1)
		return (0);
	data->floor_color = color;
	data->floor_set = 1;
	return (1);
}
/**
 * Parsea la línea de color del techo (C)
 */
int parse_ceiling_color(char *line, t_color *data)
{
	char	*rgb_str;
	int		color;

	rgb_str = ft_strtrim(line + 1, " \t");
	if (!rgb_str)
		return(printf("Memory error parsing ceiling color\n"), -1);
	color = parse_rgb(rgb_str,data);
	free(rgb_str);
	if (color == -1)
		return (0);
	data->ceiling_color = color;
	data->ceiling_set = 1;
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:14:04 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/02/23 13:53:40 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map || map->rows)
		return ;
	while (i < map->height)
	{
		free(map->rows[i]);
		i++;
	}
	free(map->rows);
	map->rows = NULL;
	map->width = 0;
	map->height = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->player_dir = 0;
}

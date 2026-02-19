/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_rendering.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:06:57 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/19 14:08:11 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

long get_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int error_checker(t_game *game, int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	memset(game, 0, sizeof(t_game));
	if (!parse_file(argv[1], game))
	{
		printf("Error: Failed to parse map file\n");
		return (1);
	}
	initialize_mlx(&game->mlx);
	if (!load_all_textures(game))
	{
		printf("Error: Failed to load textures\n");
		return (1);
	}
	return (0);
}

void clear_image(t_mlx *data)
{
	memset(data->addr, 0, screenHeight * data->line_length);
}

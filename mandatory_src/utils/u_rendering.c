/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_rendering.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:06:57 by simgarci          #+#    #+#             */
/*   Updated: 2026/03/12 13:26:34 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_texture_pixel(char *texture_data, int tex_x, int tex_y, t_textures *tex)
{
	int	pixel_index;

	if (tex_x < 0 || tex_x >= tex->tex_width \
			|| tex_y < 0 || tex_y >= tex->tex_height)
		return (0x000000);
	pixel_index = (tex_y * tex->tex_width + tex_x) * 4;
	return (*(int *)(texture_data + pixel_index));
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	error_checker(t_game *game, int argc, char **argv)
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

void	clear_image(t_mlx *data)
{
	ft_memset(data->addr, 0, SCREEN_HEIGHT * data->line_length);
}

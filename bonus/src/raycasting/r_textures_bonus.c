/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_txt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:59:08 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/25 13:55:26 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	texture_setter(t_game *game)
{
	game->txt.img[0] = mlx_xpm_file_to_image(game->mlx.mlx, game->txt.north, \
		&game->txt.tex_width, &game->txt.tex_height);
	game->txt.img[1] = mlx_xpm_file_to_image(game->mlx.mlx, \
		game->txt.south, &game->txt.tex_width, &game->txt.tex_height);
	game->txt.img[2] = mlx_xpm_file_to_image(game->mlx.mlx, \
		game->txt.west, &game->txt.tex_width, &game->txt.tex_height);
	game->txt.img[3] = mlx_xpm_file_to_image(game->mlx.mlx, \
		game->txt.east, &game->txt.tex_width, &game->txt.tex_height);
	game->txt.img[4] = mlx_xpm_file_to_image(game->mlx.mlx, \
		game->txt.door, &game->txt.tex_width, &game->txt.tex_height);
	game->txt.data[0] = mlx_get_data_addr(game->txt.img[0], \
		&game->txt.bits_per_pixel, &game->txt.line_length, &game->txt.endian);
	game->txt.data[1] = mlx_get_data_addr(game->txt.img[1], \
		&game->txt.bits_per_pixel, &game->txt.line_length, &game->txt.endian);
	game->txt.data[2] = mlx_get_data_addr(game->txt.img[2], \
		&game->txt.bits_per_pixel, &game->txt.line_length, &game->txt.endian);
	game->txt.data[3] = mlx_get_data_addr(game->txt.img[3], \
		&game->txt.bits_per_pixel, &game->txt.line_length, &game->txt.endian);
	game->txt.data[4] = mlx_get_data_addr(game->txt.img[4], \
		&game->txt.bits_per_pixel, &game->txt.line_length, &game->txt.endian);
}

int	load_all_textures(t_game *game)
{
	int	width;
	int	shift;

	width = game->txt.tex_width;
	shift = 0;
	texture_setter(game);
	while ((1 << shift) < width)
		shift++;
	game->txt.tex_width_shift = shift;
	return (1);
}

char	*get_wall_texture_fast(t_render *r, t_textures *txt)
{
	int	tex_index;

	if (r->side == 0)
	{
		if (r->step_x > 0)
			tex_index = 1;
		else
			tex_index = 0;
	}
	else
	{
		if (r->step_y > 0)
			tex_index = 3;
		else
			tex_index = 2;
	}
	return (txt->data[tex_index]);
}

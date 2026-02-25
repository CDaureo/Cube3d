/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_textures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:59:08 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/25 13:55:26 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


int load_all_textures(t_game *game)
{
	game->textures.img[0] = mlx_xpm_file_to_image(game->mlx.mlx, game->textures.north, 
												   &game->textures.tex_width, &game->textures.tex_height);
	game->textures.img[1] = mlx_xpm_file_to_image(game->mlx.mlx, game->textures.south, 
												   &game->textures.tex_width, &game->textures.tex_height);
	game->textures.img[2] = mlx_xpm_file_to_image(game->mlx.mlx, game->textures.west, 
												   &game->textures.tex_width, &game->textures.tex_height);
	game->textures.img[3] = mlx_xpm_file_to_image(game->mlx.mlx, game->textures.east, 
												   &game->textures.tex_width, &game->textures.tex_height);
	game->textures.img[4] = mlx_xpm_file_to_image(game->mlx.mlx, game->textures.door, 
												   &game->textures.tex_width, &game->textures.tex_height);
	game->textures.data[0] = mlx_get_data_addr(game->textures.img[0], &game->textures.bits_per_pixel,
												&game->textures.line_length, &game->textures.endian);
	game->textures.data[1] = mlx_get_data_addr(game->textures.img[1], &game->textures.bits_per_pixel,
												&game->textures.line_length, &game->textures.endian);
	game->textures.data[2] = mlx_get_data_addr(game->textures.img[2], &game->textures.bits_per_pixel,
												&game->textures.line_length, &game->textures.endian);
	game->textures.data[3] = mlx_get_data_addr(game->textures.img[3], &game->textures.bits_per_pixel,
												&game->textures.line_length, &game->textures.endian);
	game->textures.data[4] = mlx_get_data_addr(game->textures.img[4], &game->textures.bits_per_pixel,
												&game->textures.line_length, &game->textures.endian);
	int width = game->textures.tex_width;
	int shift = 0;
	while ((1 << shift) < width) shift++;
		game->textures.tex_width_shift = shift;
	return (1);
}

char *get_wall_texture_fast(t_render *r, t_textures *textures)
{
	int tex_index = (r->side << 1) | (r->side == 0 ? (r->step_x > 0) : (r->step_y > 0));

	return textures->data[tex_index];
}

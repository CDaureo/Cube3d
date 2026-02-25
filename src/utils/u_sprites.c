/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_spr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:06:37 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/18 17:07:39 by simgarci         ###   ########.fr       */
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

int	get_spr_pixel(char *spr_data, int tex_x, int tex_y, t_spr_system *spr)
{
	int	pixel_index;

	pixel_index = (tex_y * spr->grass_width + tex_x) * 4;
	if (tex_x < 0 || tex_x >= spr->grass_width || tex_y < 0 \
			|| tex_y >= spr->grass_height)
		return (0xFF00FF);
	return (*(int *)(spr_data + pixel_index));
}

void	grass_loop_generating(t_game *game, \
		t_minimap *mp, t_spr_system *spr, int i)
{
	if (get_map_value(&game->maps, mp->map_x, mp->map_y, game) == 0)
	{
		spr->grass_per_tile = 1 + (rand() % 2);
		while (i < spr->grass_per_tile && game->spr.spr_count < spr->max_sprs)
		{
			mp->rand_x = mp->map_x + 0.1 + (rand() % 80) / 100.0;
			mp->rand_y = mp->map_y + 0.1 + (rand() % 80) / 100.0;
			if (mp->rand_x < mp->map_x + 0.2 || mp->rand_x > mp->map_x + 0.8)
			{
				i++;
				continue ;
			}
			if (mp->rand_y < mp->map_y + 0.2 || mp->rand_y > mp->map_y + 0.8)
			{
				i++;
				continue ;
			}
			spr->grass_type = rand() % 2;
			game->spr.sprs[game->spr.spr_count].x = mp->rand_x;
			game->spr.sprs[game->spr.spr_count].y = mp->rand_y;
			game->spr.sprs[game->spr.spr_count].texture_index = spr->grass_type;
			game->spr.spr_count++;
			i++;
		}
	}
}

void	generate_grass_sprite(t_game *game, t_minimap *minimap)
{
	t_spr_system	spr;
	int				i;

	spr.max_sprs = MAX_sprS;
	game->spr.spr_count = 0;
	game->spr.sprs = malloc(sizeof(t_spr) * spr.max_sprs);
	minimap->map_y = 0;
	while (minimap->map_y < game->maps.height)
	{
		minimap->map_x = 0;
		while (minimap->map_x < game->maps.width)
		{
			i = 0;
			grass_loop_generating(game, minimap, &spr, i);
			minimap->map_x++;
		}
		minimap->map_y++;
	}
}

int	load_grass_texture(t_game *game)
{
	int	temp_vars[3];

	game->spr.grass_img[0] = mlx_xpm_file_to_image(game->mlx.mlx, \
			"textures/grass.xpm", \
			&game->spr.grass_width, &game->spr.grass_height);
	if (!game->spr.grass_img[0])
	{
		printf("Failed to load grass texture 1\n");
		return (0);
	}
	game->spr.grass_img[1] = mlx_xpm_file_to_image(game->mlx.mlx, \
			"textures/grass2.xpm", \
			&game->spr.grass_width, &game->spr.grass_height);
	if (!game->spr.grass_img[1])
	{
		game->spr.grass_img[1] = game->spr.grass_img[0];
		printf("Using same grass texture for variety\n");
	}
	game->spr.grass_data[0] = mlx_get_data_addr(game->spr.grass_img[0], \
			&temp_vars[0], &temp_vars[1], &temp_vars[2]);
	game->spr.grass_data[1] = mlx_get_data_addr(game->spr.grass_img[1], \
			&temp_vars[0], &temp_vars[1], &temp_vars[2]);
	return (1);
}

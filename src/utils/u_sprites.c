/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_sprites.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:06:37 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/18 17:07:39 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int get_texture_pixel(char *texture_data, int tex_x, int tex_y, t_textures *tex)
{
	int pixel_index;

	if (tex_x < 0 || tex_x >= tex->tex_width || tex_y < 0 || tex_y >= tex->tex_height)
		return (0x000000);
	pixel_index = (tex_y * tex->tex_width + tex_x) * 4;
	return (*(int *)(texture_data + pixel_index));
}

int get_sprite_pixel(char *sprite_data, int tex_x, int tex_y, t_sprite_system *sprites)
{
	int pixel_index;

	pixel_index = (tex_y * sprites->grass_width + tex_x) * 4;
	if (tex_x < 0 || tex_x >= sprites->grass_width || tex_y < 0 || tex_y >= sprites->grass_height)
		return 0xFF00FF;
	return (*(int *)(sprite_data + pixel_index));
}

void grass_loop_generating(t_game *game, t_minimap *minimap, t_sprite_system *sprites, int i)
{
	if (get_map_value(&game->maps, minimap->map_x, minimap->map_y, game) == 0)
	{
		sprites->grass_per_tile = 1 + (rand() % 2);
		while(i < sprites->grass_per_tile && game->sprites.sprite_count < sprites->max_sprites)
		{
			minimap->rand_x = minimap->map_x + 0.1 + (rand() % 80) / 100.0;
			minimap->rand_y = minimap->map_y + 0.1 + (rand() % 80) / 100.0;
			if (minimap->rand_x < minimap->map_x + 0.2 || minimap->rand_x > minimap->map_x + 0.8)
			{
				i++;
				continue;
			}
			if (minimap->rand_y < minimap->map_y + 0.2 || minimap->rand_y > minimap->map_y + 0.8)
			{
				i++;
				continue;
			}
			sprites->grass_type = rand() % 2;
			game->sprites.sprites[game->sprites.sprite_count].x = minimap->rand_x;
			game->sprites.sprites[game->sprites.sprite_count].y = minimap->rand_y;
			game->sprites.sprites[game->sprites.sprite_count].texture_index = sprites->grass_type;
			game->sprites.sprite_count++;
			i++;
		}
	}
}

void generate_grass_sprites(t_game *game, t_minimap *minimap)
{
	t_sprite_system sprites;
	int i;

	sprites.max_sprites = MAX_SPRITES;
	game->sprites.sprite_count = 0;
	game->sprites.sprites = malloc(sizeof(t_sprite) * sprites.max_sprites);
	minimap->map_y = 0;
	while(minimap->map_y < game->maps.height)
	{
		minimap->map_x = 0;
		while(minimap->map_x < game->maps.width)
		{
			i = 0;
			grass_loop_generating(game, minimap, &sprites, i);
			minimap->map_x++;
		}
		minimap->map_y++; 
	printf("Generated %d grass sprites\n", game->sprites.sprite_count);
	}
}

int load_grass_texture(t_game *game)
{
	game->sprites.grass_img[0] = mlx_xpm_file_to_image(game->mlx.mlx, "textures/grass.xpm", 
													   &game->sprites.grass_width, &game->sprites.grass_height);
	if (!game->sprites.grass_img[0])
	{
		printf("Failed to load grass texture 1\n");
		return (0);
	}
	game->sprites.grass_img[1] = mlx_xpm_file_to_image(game->mlx.mlx, "textures/grass2.xpm", 
													   &game->sprites.grass_width, &game->sprites.grass_height);
	if (!game->sprites.grass_img[1])
	{
		game->sprites.grass_img[1] = game->sprites.grass_img[0];
		printf("Using same grass texture for variety\n");
	}
	int temp_vars[3];
	game->sprites.grass_data[0] = mlx_get_data_addr(game->sprites.grass_img[0], 
													&temp_vars[0], &temp_vars[1], &temp_vars[2]);
	game->sprites.grass_data[1] = mlx_get_data_addr(game->sprites.grass_img[1], 
													&temp_vars[0], &temp_vars[1], &temp_vars[2]);
	return (1);
}

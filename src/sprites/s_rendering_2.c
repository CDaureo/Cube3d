/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_rendering_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:08:56 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/18 17:09:16 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void calculate_sprite_distances(t_mlx *mlx, t_sprite_system *sprites, int *rendered_count)
{
	int i;
	double dx;
	double dy;

	i = 0;
	*rendered_count = 0;
	while(i < sprites->sprite_count)
	{
		dx = sprites->sprites[i].x - mlx->posX;
		dy = sprites->sprites[i].y - mlx->posY;
		sprites->sprites[i].distance = dx * dx + dy * dy;
		if (sprites->sprites[i].distance > 64.0)
			sprites->sprites[i].distance = -1;
		else
			(*rendered_count)++;
		i++;
	}
}

void swap_sprites(t_sprite *sprite1, t_sprite *sprite2)
{
	t_sprite temp;

	temp = *sprite1;
	*sprite1 = *sprite2;
	*sprite2 = temp;
}

void sort_sprites_by_distance(t_sprite_system *sprites)
{
	int i;
	int j;

	i = 0;
	while(i < sprites->sprite_count - 1)
	{
		j = 0;
		while(j < sprites->sprite_count - 1)
		{
			if (sprites->sprites[j].distance >= 0 && sprites->sprites[j + 1].distance >= 0 &&
				sprites->sprites[j].distance < sprites->sprites[j + 1].distance)
			{
				swap_sprites(&sprites->sprites[j], &sprites->sprites[j + 1]);
			}
			j++;
		}
		i++;
	}
}

void render_visible_sprites(t_mlx *mlx, t_sprite_system *sprites)
{
	int i;

	i = 0;
	while(i < sprites->sprite_count)
	{
		if (sprites->sprites[i].distance >= 0)
			render_single_sprite(mlx, &sprites->sprites[i], sprites);
		i++;
	}
}

void render_sprites(t_mlx *mlx, t_sprite_system *sprites)
{
	int rendered_count;

	calculate_sprite_distances(mlx, sprites, &rendered_count);
	sort_sprites_by_distance(sprites);
	render_visible_sprites(mlx, sprites);
}

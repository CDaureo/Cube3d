/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_drawing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:23:58 by simgarci          #+#    #+#             */
/*   Updated: 2026/03/11 18:03:12 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	if (!data -> addr)
	{
		printf ("Error: data->addr is NULL\n");
		return ;
	}
	if (x >= 0 && y >= 0 && x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * \
			(data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

t_door	*find_door(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (&game->doors[i]);
		i++;
	}
	return (NULL);
}

void	apply_dda(t_mlx *mlx, t_render *r, t_map *map, t_game *game)
{
	int	step_count;

	step_count = 0;
	initialize_dda_step_x(mlx, r);
	initialize_dda_step_y(mlx, r);
	r->hit = 0;
	r->hit_type = 0;
	while (r->hit == 0)
	{
		step_count++;
		perform_dda_step(r);
		check_wall_hit(r, map, game);
	}
}

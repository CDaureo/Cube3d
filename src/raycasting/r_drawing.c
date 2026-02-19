/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   r_testing.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: simgarci <simgarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/01/22 13:03:24 by simgarci		  #+#	#+#			 */
/*   Updated: 2026/02/16 13:42:42 by simgarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	if (!data -> addr)
	{
		printf("Error: data->addr is NULL\n");
		return ;
	}
	if (x >= 0 && y >= 0 && x < screenWidth && y < screenHeight)
	{
		dst = data->addr + (y * data->line_length + x * \
			(data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

t_door *find_door(t_game *game, int x, int y)
{
	for (int i = 0; i < game->door_count; i++)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (&game->doors[i]);
	}
	return (NULL);
}

void apply_dda(t_mlx *mlx, t_render *r, t_map *map, t_game *game)
{
	int step_count;

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

int apply_vignette(int color, int x, int y)
{
	double center_x = screenWidth / 2.0;
	double center_y = screenHeight / 2.0;
	double dx = x - center_x;
	double dy = y - center_y;
	double max_distance = sqrt(center_x * center_x + center_y * center_y);
	double distance = sqrt(dx * dx + dy * dy) / max_distance;
	double vignette_strength = 0.7;
	double vignette_factor = distance * vignette_strength;
	int r = ((color >> 16) & 0xFF);
	int g = ((color >> 8) & 0xFF);
	int b = (color & 0xFF);

	if (vignette_factor > vignette_strength) 
		vignette_factor = vignette_strength;
	r = (int)(r * (1.0 - vignette_factor));
	g = (int)(g * (1.0 - vignette_factor));
	b = (int)(b * (1.0 - vignette_factor));
	return ((r << 16) | (g << 8) | b);
}


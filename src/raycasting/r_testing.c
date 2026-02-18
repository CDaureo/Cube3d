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



long get_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

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

int get_map_value(t_map *map, int x, int y, t_game *game)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (1);
	
	char cell = map->rows[y][x];
	
	if (cell == '1')
		return (1);
	else if (cell == 'D')
	{
		t_door *door = find_door(game, x, y);
		if (door && door->is_open)
			return (0);
		else
			return (1);
	}
	else if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
		return (0);
	else
		return (1);
}

int load_texture(t_mlx *mlx, char *path, void **img, char **data, t_textures *tex)
{
	if (!path)
		return (0);
	FILE *test_file = fopen(path, "r");
	if (!test_file)
		return (0);
	fclose(test_file);
	*img = mlx_xpm_file_to_image(mlx->mlx, path, &tex->tex_width, &tex->tex_height);
	if (!*img)
		return (0);
	*data = mlx_get_data_addr(*img, &tex->bits_per_pixel, &tex->line_length, &tex->endian);
	if (!*data)
		return (0);
	return (1);
}

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

static inline char *get_wall_texture_fast(t_render *r, t_textures *textures)
{
	int tex_index = (r->side << 1) | (r->side == 0 ? (r->stepX > 0) : (r->stepY > 0));

	return textures->data[tex_index];
}

int key_hook(int keycode, t_mlx *mlx)
{
	(void)mlx;

	if(keycode == 65307)
		exit(0);
	return (0);
}

int close_hook(t_mlx *mlx)
{
	(void)mlx;

	exit(0);
}

static void clear_image(t_mlx *data)
{
	memset(data->addr, 0, screenHeight * data->line_length);
}

void draw_dot(t_mlx *mlx, int dot_size, int center_x, int center_y)
{
	int y;
	int x;
	int pixel_x;
	int pixel_y;

	y = -dot_size;
	while(y <= dot_size)
	{
		x = -dot_size;
		while(x <= dot_size)
		{
			if(x*x + y*y <= dot_size*dot_size)
			{
				pixel_x = center_x + x;
				pixel_y = center_y + y;
				if(pixel_x >= 0 && pixel_y >= 0 && pixel_x < screenWidth && pixel_y < screenHeight)
				{
					ft_mlx_pixel_put(mlx, pixel_x, pixel_y, 0xFFFFFF);
				}
			}
			x++;
		}
		y++;
	}
}

void draw_crosshair(t_mlx *mlx)
{
	t_minimap map;

	map.center_x = screenWidth / 2;
	map.center_y = screenHeight / 2;
	map.dot_size = 2;
	map.outline_size = map.dot_size + 1;
	map.y = -map.outline_size;
	while(map.y <= map.outline_size)
	{
		while(map.x <= map.outline_size)
		{
			map.x = -map.outline_size;
			if(map.x*map.x + map.y*map.y <= map.outline_size*map.outline_size)
			{
				map.pixel_x = map.center_x + map.x;
				map.pixel_y = map.center_y + map.y;
				if(map.pixel_x >= 0 && map.pixel_y >= 0 && map.pixel_x < screenWidth && map.pixel_y < screenHeight)
					ft_mlx_pixel_put(mlx, map.pixel_x, map.pixel_y, 0x000000);
			}
			map.x++;
		}
		map.y++;
	}
	draw_dot(mlx, map.dot_size, map.center_x, map.center_y);
}

void set_north_direction(t_mlx *mlx, double plane_length)
{
	mlx->dirX = 0;
	mlx->dirY = -1;
	mlx->planeX = plane_length;
	mlx->planeY = 0;
}

void set_south_direction(t_mlx *mlx, double plane_length)
{
	mlx->dirX = 0;
	mlx->dirY = 1;
	mlx->planeX = -plane_length;
	mlx->planeY = 0;
}

void set_east_direction(t_mlx *mlx, double plane_length)
{
	mlx->dirX = 1;
	mlx->dirY = 0;
	mlx->planeX = 0;
	mlx->planeY = plane_length;
}

void set_west_direction(t_mlx *mlx, double plane_length)
{
	mlx->dirX = -1;
	mlx->dirY = 0;
	mlx->planeX = 0;
	mlx->planeY = -plane_length;
}

void set_player_direction(t_mlx *mlx, char player_dir, double plane_length)
{
	if (player_dir == 'N')
		set_north_direction(mlx, plane_length);
	else if (player_dir == 'S')
		set_south_direction(mlx, plane_length);
	else if (player_dir == 'E')
		set_east_direction(mlx, plane_length);
	else if (player_dir == 'W')
		set_west_direction(mlx, plane_length);
	else
		set_west_direction(mlx, plane_length);
}

void initialize_player_from_map(t_mlx *mlx, t_map *map)
{
	mlx->posX = map->player_x + 0.5;
	mlx->posY = map->player_y + 0.5;
	mlx->pitch = 0;
	set_player_direction(mlx, map->player_dir, 0.80);
}


void check_wall_hit(t_render *r, t_map *map, t_game *game)
{
	char cell;
	t_door *door;

	cell = map->rows[r->mapY][r->mapX];
	if (cell == '1')
	{
		r->hit = 1;
		r->hit_type = 1;
	}
	else if (cell == 'D')
	{
		door = find_door(game, r->mapX, r->mapY);
		if (door && !door->is_open)
		{
			r->hit = 1;
			r->hit_type = 2;
		}
	}
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

void interact_with_door(t_game *game)
{
	float distances[] = {0.3, 0.6, 0.9, 1.2, 1.5};
	int num_distances = 5;

	for (int i = 0; i < num_distances; i++)
	{
		float check_x = game->mlx.posX + game->mlx.dirX * distances[i];
		float check_y = game->mlx.posY + game->mlx.dirY * distances[i];
		int map_x = (int)check_x;
		int map_y = (int)check_y;

		if (map_x < 0 || map_x >= game->maps.width || 
			map_y < 0 || map_y >= game->maps.height)
			continue;
		if (game->maps.rows[map_y][map_x] == 'D')
		{
			t_door *door = find_door(game, map_x, map_y);
			if (door)
			{
				door->is_open = !door->is_open;
				printf("Door %s at (%d, %d)\n", 
					   door->is_open ? "opened" : "closed", map_x, map_y);
				return;
			}
		}
	}
}


static int error_checker(t_game *game, int argc, char **argv)
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

int main(int argc, char **argv)
{
	t_game game;
	t_minimap minimap;

	if(error_checker(&game, argc, argv))
		return (1);
	initialize_player_from_map(&game.mlx, &game.maps);
	load_grass_texture(&game);
	generate_grass_sprites(&game, &minimap);
	mlx_hook(game.mlx.win, 2, 1L << 0, handle_keys, &game);
	mlx_hook(game.mlx.win, 3, 1L << 1, handle_key_release, &game);
	mlx_hook(game.mlx.win, 4, 1L << 2, handle_mouse_press, &game.mlx);
	mlx_hook(game.mlx.win, 6, 1L << 6, handle_mouse_move, &game.mlx);
	mlx_hook(game.mlx.win, 17, 0, close_hook, &game.mlx);
	mlx_loop_hook(game.mlx.mlx, render_loop_wrapper, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}

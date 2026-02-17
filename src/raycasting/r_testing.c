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

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../minilibx-linux/mlx.h"
#include "sys/time.h"
#include "../../includes/cub3d.h"

#define MAX_SPRITES 2000
#define MOVEMENT_FPS 60
#define RENDER_FPS 60
#define TARGET_FPS 60
#define FRAME_TIME_MS (1000 / TARGET_FPS)
#define screenWidth 1920
#define screenHeight 1080
#define MOVE_SPEED 0.03
#define ROT_SPEED 0.015
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_UP_ARROW 65364
#define KEY_DOWN_ARROW 65362
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define MOUSE_SENS_X 0.001
#define MOUSE_SENS_Y 1.0  
#define MINIMAP_SIZE 200
#define MINIMAP_SCALE 8
#define MINIMAP_OFFSET 20
#define KEY_SHIFT 65505
#define KEY_INTERACT 101

typedef struct s_mouse {
	int center_x ;
	int center_y;
	int delta_x;
	int delta_y ;
	double rotation;
	double oldDirX;
	double oldPlaneX;
}	t_mouse;

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

void init_minimap(t_minimap *minimap, t_mlx *mlx)
{
	minimap->map_start_x = screenWidth - MINIMAP_SIZE - MINIMAP_OFFSET;
	minimap->map_start_y = screenHeight - MINIMAP_SIZE - MINIMAP_OFFSET;
	minimap->center_x = minimap->map_start_x + MINIMAP_SIZE / 2;
	minimap->center_y = minimap->map_start_y + MINIMAP_SIZE / 2;
	minimap->radius = MINIMAP_SIZE / 2;
	minimap->player_pixel_x = minimap->center_x;
	minimap->player_pixel_y = minimap->center_y;
	minimap->player_angle = atan2(mlx->dirY, mlx->dirX) + M_PI/2;  // Was - M_PI/2
	minimap->arrow_length = 6;
	minimap->arrow_width = 4;
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

void background_check(t_minimap *minimap, t_mlx *mlx, t_game *game, t_map *map)
{
	if(minimap->distance_squared <= minimap->radius * minimap->radius)
	{
		minimap->rel_x = minimap->dx / (double)(MINIMAP_SIZE / 2);
		minimap->rel_y = minimap->dy / (double)(MINIMAP_SIZE / 2);
		minimap->rotated_x = minimap->rel_x * cos(minimap->player_angle) - minimap->rel_y * sin(minimap->player_angle);
		minimap->rotated_y = minimap->rel_x * sin(minimap->player_angle) + minimap->rel_y * cos(minimap->player_angle);
		double map_scale = 8.0;
		minimap->world_x = mlx->posX + minimap->rotated_x * map_scale;   
		minimap->world_y = mlx->posY + minimap->rotated_y * map_scale;  
		minimap->map_x = (int)minimap->world_x;
		minimap->map_y = (int)minimap->world_y;
		if(get_map_value(map, minimap->map_x, minimap->map_y, game) == 1)
			minimap->color = 0xFFFFFF;
		else
			minimap->color = 0x333333;
		minimap->screen_x = minimap->map_start_x + minimap->pixel_x;
		minimap->screen_y = minimap->map_start_y + minimap->pixel_y;
		if(minimap->screen_x < screenWidth && minimap->screen_y < screenHeight)
			ft_mlx_pixel_put(mlx, minimap->screen_x, minimap->screen_y, minimap->color);
	}
}

void draw_map_background(t_mlx *mlx, t_minimap *minimap, t_map *map, t_game *game)
{ 
	minimap->pixel_y = 0;

	while(minimap->pixel_y < MINIMAP_SIZE)
	{
		minimap->pixel_x = 0;
		while(minimap->pixel_x < MINIMAP_SIZE)
		{	   
			minimap->dx = minimap->pixel_x - MINIMAP_SIZE / 2;
			minimap->dy = minimap->pixel_y - MINIMAP_SIZE / 2;
			minimap->distance_squared = minimap->dx * minimap->dx + minimap->dy * minimap->dy;
			
			minimap->pixel_x++;
		}
		minimap->pixel_y++;
	}
}

void draw_arrow_body(t_mlx *mlx, t_minimap *minimap)
{
	minimap->scan_y = -minimap->arrow_length;
	
	while(minimap->scan_y <= minimap->arrow_length)
	{
		if(minimap->scan_y < 0)
			minimap->width_at_y = (minimap->arrow_width * (minimap->arrow_length + minimap->scan_y)) / minimap->arrow_length;
		else
			minimap->width_at_y = minimap->arrow_width;
		minimap->dx = -minimap->width_at_y;
		while(minimap->dx <= minimap->width_at_y)
		{   
			minimap->current_x = minimap->player_pixel_x + minimap->dx;
			minimap->current_y_adj = minimap->player_pixel_y + minimap->scan_y;
			minimap->arrow_dx = minimap->current_x - minimap->center_x;
			minimap->arrow_dy = minimap->current_y_adj - minimap->center_y;
			
			if(minimap->arrow_dx * minimap->arrow_dx + minimap->arrow_dy * minimap->arrow_dy <= minimap->radius * minimap->radius)
			{
				if(minimap->current_x >= 0 && minimap->current_y_adj >= 0 && minimap->current_x < screenWidth && minimap->current_y_adj < screenHeight)
					ft_mlx_pixel_put(mlx, minimap->current_x, minimap->current_y_adj, 0xFF0000);
			}
			minimap->dx++;
		}
		minimap->scan_y++;
	}
}

void draw_arrow_outline(t_mlx *mlx, t_minimap *minimap)
{
	int i = 0;

	minimap->tip_x = minimap->player_pixel_x;
	minimap->tip_y = minimap->player_pixel_y - minimap->arrow_length;
	minimap->base_center_x = minimap->player_pixel_x;
	minimap->base_center_y = minimap->player_pixel_y + minimap->arrow_length;
	minimap->base_left_x = minimap->base_center_x - minimap->arrow_width;
	minimap->base_left_y = minimap->base_center_y;
	minimap->base_right_x = minimap->base_center_x + minimap->arrow_width;
	minimap->base_right_y = minimap->base_center_y;
	while(i <= 20)
	{
		minimap->lx1 = minimap->base_left_x + (int)((minimap->tip_x - minimap->base_left_x) * i / 20.0);
		minimap->ly1 = minimap->base_left_y + (int)((minimap->tip_y - minimap->base_left_y) * i / 20.0);
		minimap->lx2 = minimap->base_right_x + (int)((minimap->tip_x - minimap->base_right_x) * i / 20.0);
		minimap->ly2 = minimap->base_right_y + (int)((minimap->tip_y - minimap->base_right_y) * i / 20.0);
		
		if(i <= 10)
		{
			minimap->lx3 = minimap->base_left_x + (int)((minimap->base_right_x - minimap->base_left_x) * i / 10.0);
			minimap->ly3 = minimap->base_left_y + (int)((minimap->base_right_y - minimap->base_left_y) * i / 10.0);
			minimap->outline_dx = minimap->lx3 - minimap->center_x;
			minimap->outline_dy = minimap->ly3 - minimap->center_y;
			
			if(minimap->outline_dx * minimap->outline_dx + minimap->outline_dy * minimap->outline_dy <= minimap->radius * minimap->radius)
			{
				if(minimap->lx3 >= 0 && minimap->ly3 >= 0 && minimap->lx3 < screenWidth && minimap->ly3 < screenHeight)
					ft_mlx_pixel_put(mlx, minimap->lx3, minimap->ly3, 0xFFFFFF);
			}
		}
		minimap->outline_dx1 = minimap->lx1 - minimap->center_x;
		minimap->outline_dy1 = minimap->ly1 - minimap->center_y;
		minimap->outline_dx2 = minimap->lx2 - minimap->center_x;
		minimap->outline_dy2 = minimap->ly2 - minimap->center_y;
		if(minimap->outline_dx1 * minimap->outline_dx1 + minimap->outline_dy1 * minimap->outline_dy1 <= minimap->radius * minimap->radius)
		{
			if(minimap->lx1 >= 0 && minimap->ly1 >= 0 && minimap->lx1 < screenWidth && minimap->ly1 < screenHeight)
				ft_mlx_pixel_put(mlx, minimap->lx1, minimap->ly1, 0xFFFFFF);
		}
		if(minimap->outline_dx2 * minimap->outline_dx2 + minimap->outline_dy2 * minimap->outline_dy2 <= minimap->radius * minimap->radius)
		{
			if(minimap->lx2 >= 0 && minimap->ly2 >= 0 && minimap->lx2 < screenWidth && minimap->ly2 < screenHeight)
				ft_mlx_pixel_put(mlx, minimap->lx2, minimap->ly2, 0xFFFFFF);
		}
		i++;
	}
}

void draw_minimap_circle(t_mlx *mlx, t_minimap *minimap)
{
	minimap->angle = 0;

	while(minimap->angle < 360)
	{  
		minimap->radian = minimap->angle * M_PI / 180.0;
		minimap->border_x = minimap->center_x + (int)(cos(minimap->radian) * minimap->radius);
		minimap->border_y = minimap->center_y + (int)(sin(minimap->radian) * minimap->radius);
		if(minimap->border_x >= 0 && minimap->border_y >= 0 && minimap->border_x < screenWidth && minimap->border_y < screenHeight)
			ft_mlx_pixel_put(mlx, minimap->border_x, minimap->border_y, 0xFFFFFF);
		minimap->inner_border_x = minimap->center_x + (int)(cos(minimap->radian) * (minimap->radius - 1));
		minimap->inner_border_y = minimap->center_y + (int)(sin(minimap->radian) * (minimap->radius - 1));
		if(minimap->inner_border_x >= 0 && minimap->inner_border_y >= 0 && minimap->inner_border_x < screenWidth && minimap->inner_border_y < screenHeight)
			ft_mlx_pixel_put(mlx, minimap->inner_border_x, minimap->inner_border_y, 0xFFFFFF);
			
		minimap->angle++;
	}
}

void draw_player_dot(t_mlx *mlx, t_minimap *minimap)
{
	ft_mlx_pixel_put(mlx, minimap->player_pixel_x, minimap->player_pixel_y, 0xFFFF00);
}

void draw_minimap(t_mlx *mlx, t_map *map, t_game *game)
{
	t_minimap minimap;
	init_minimap(&minimap, mlx);
	draw_map_background(mlx, &minimap, map, game);
	draw_arrow_body(mlx, &minimap);
	draw_arrow_outline(mlx, &minimap);   
	draw_player_dot(mlx, &minimap);
	draw_minimap_circle(mlx, &minimap);
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

void generate_grass_sprites(t_game *game, t_minimap *minimap)
{
    int max_sprites;
    int grass_type;
    int grass_per_tile;
    int i;

    max_sprites = MAX_SPRITES;
    game->sprites.sprite_count = 0;
    game->sprites.sprites = malloc(sizeof(t_sprite) * max_sprites);
    minimap->map_y = 0;
    while(minimap->map_y < game->maps.height)
    {
        minimap->map_x = 0;
        while(minimap->map_x < game->maps.width)
        {
            if (get_map_value(&game->maps, minimap->map_x, minimap->map_y, game) == 0)
            {
                grass_per_tile = 1 + (rand() % 2);
                i = 0;
                while(i < grass_per_tile && game->sprites.sprite_count < max_sprites)
                {
                    minimap->rand_x = minimap->map_x + 0.1 + (rand() % 80) / 100.0;
                    minimap->rand_y = minimap->map_y + 0.1 + (rand() % 80) / 100.0;
                    if (minimap->rand_x < minimap->map_x + 0.2 || minimap->rand_x > minimap->map_x + 0.8) {
                        i++;
                        continue;
                    }
                    if (minimap->rand_y < minimap->map_y + 0.2 || minimap->rand_y > minimap->map_y + 0.8) {
                        i++;
                        continue;
                    }
                    grass_type = rand() % 2;
                    game->sprites.sprites[game->sprites.sprite_count].x = minimap->rand_x;
                    game->sprites.sprites[game->sprites.sprite_count].y = minimap->rand_y;
                    game->sprites.sprites[game->sprites.sprite_count].texture_index = grass_type;
                    game->sprites.sprite_count++;
                    i++;
                }
            }
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

void render_single_sprite(t_mlx *mlx, t_sprite *sprite, t_sprite_system *sprites)
{
    int stripe;
    int y;
    sprites->spriteX = sprite->x - mlx->posX;
    sprites->spriteY = sprite->y - mlx->posY;
    sprites->invDet = 1.0 / (mlx->planeX * mlx->dirY - mlx->dirX * mlx->planeY);
    sprites->transformX = sprites->invDet * (mlx->dirY * sprites->spriteX - mlx->dirX * sprites->spriteY);
    sprites->transformY = sprites->invDet * (-mlx->planeY * sprites->spriteX + mlx->planeX * sprites->spriteY);
    if (sprites->transformY <= 0)
        return;
    sprites->spriteScreenX = (int)((screenWidth / 2) * (1 + sprites->transformX / sprites->transformY));
    sprites->spriteHeight = abs((int)(screenHeight / sprites->transformY)) / 8;
    sprites->spriteWidth = abs((int)(screenHeight / sprites->transformY)) / 6;
    sprites->horizonY = screenHeight / 2 + (int)mlx->pitch;
    sprites->groundY = sprites->horizonY + (int)(screenHeight / (2.0 * sprites->transformY));
    sprites->drawStartY = sprites->groundY - sprites->spriteHeight;
    sprites->drawEndY = sprites->groundY;
    if (sprites->drawStartY < 0)
        sprites->drawStartY = 0;
    if (sprites->drawEndY >= screenHeight)
        sprites->drawEndY = screenHeight - 1;
    if (sprites->drawStartY >= sprites->drawEndY) 
        return;
    sprites->drawStartX = -sprites->spriteWidth / 2 + sprites->spriteScreenX;
    if (sprites->drawStartX < 0)
        sprites->drawStartX = 0;
    sprites->drawEndX = sprites->spriteWidth / 2 + sprites->spriteScreenX;
    if (sprites->drawEndX >= screenWidth)
        sprites->drawEndX = screenWidth - 1;
    if (sprites->drawStartX >= sprites->drawEndX)
        return;
    char *current_grass_data = sprites->grass_data[sprite->texture_index];
    stripe = sprites->drawStartX;
    while(stripe < sprites->drawEndX)
    {
        // Fixed z-buffer check: only skip if sprite is BEHIND the wall
        if (stripe >= 0 && stripe < screenWidth && sprites->transformY > mlx->zbuffer[stripe]) 
        {
            stripe++;
            continue;
        }
            
        int texX = (int)((stripe - sprites->drawStartX) * sprites->grass_width / (sprites->drawEndX - sprites->drawStartX));
        if (texX < 0) texX = 0;
        if (texX >= sprites->grass_width) texX = sprites->grass_width - 1;
        y = sprites->drawStartY;
        while(y < sprites->drawEndY)
        {
            int texY = (int)((y - sprites->drawStartY) * sprites->grass_height / (sprites->drawEndY - sprites->drawStartY));
            if (texY < 0) texY = 0;
            if (texY >= sprites->grass_height) texY = sprites->grass_height - 1;
            int color = get_sprite_pixel(current_grass_data, texX, texY, sprites);
            if (color == 0xFF00FF || (color & 0xFF00FF) == 0xFF00FF) 
            {
                y++;
                continue;
            }
            if (stripe >= 0 && stripe < screenWidth && y >= 0 && y < screenHeight)
                ft_mlx_pixel_put(mlx, stripe, y, color);
            y++;
        }
        stripe++;
    }
}

void render_sprites(t_mlx *mlx, t_sprite_system *sprites)
{
	int rendered_count;
	int i;
	int j;
	double dx;
	double dy;

	i = 0;
	rendered_count = 0;
	while(i < sprites->sprite_count)
	{
		dx = sprites->sprites[i].x - mlx->posX;
		dy = sprites->sprites[i].y - mlx->posY;
		sprites->sprites[i].distance = dx * dx + dy * dy;
		if (sprites->sprites[i].distance > 64.0)
			sprites->sprites[i].distance = -1;
		else
			rendered_count++;
		i++;
	}
	i = 0;
	while(i < sprites->sprite_count - 1)
	{
		j = 0;
		while(j < sprites->sprite_count - 1)
		{
			if (sprites->sprites[j].distance >= 0 && sprites->sprites[j + 1].distance >= 0 &&
				sprites->sprites[j].distance < sprites->sprites[j + 1].distance)
			{
				t_sprite temp = sprites->sprites[j];
				sprites->sprites[j] = sprites->sprites[j + 1];
				sprites->sprites[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	i  = 0;
	while(i < sprites->sprite_count)
	{
		if (sprites->sprites[i].distance >= 0)
			render_single_sprite(mlx, &sprites->sprites[i], sprites);
		i++;
	}
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

void render_start(t_mlx *mlx, t_render *r)
{
	r->cameraX = 2 * r->x / (double)screenWidth - 1;
	r->rayDirX = mlx->dirX + mlx->planeX * r->cameraX;
	r->rayDirY = mlx->dirY + mlx->planeY * r->cameraX;
	r->mapX = (int)mlx->posX;
	r->mapY = (int)mlx->posY;
	if (r->rayDirY == 0)
		r->deltaDistY = 1e30;
	else
		r->deltaDistY = fabs(1 / r->rayDirY);

	if (r->rayDirX == 0)
		r->deltaDistX = 1e30;
	else
		r->deltaDistX = fabs(1 / r->rayDirX);
}

void draw_ceiling_floor(t_mlx *mlx, t_color *colors, int x, int draw_start, int draw_end)
{
	int y;

	y = 0;
	while (y < draw_start)
	{
		ft_mlx_pixel_put(mlx, x, y, colors->ceiling_color);
		y++;
	}
	y = draw_end + 1;
	while (y < screenHeight)
	{
		ft_mlx_pixel_put(mlx, x, y, colors->floor_color);
		y++;
	}
}

void apply_dda(t_mlx *mlx, t_render *r, t_map *map, t_game *game)
{
	if (r->rayDirX < 0)
	{
		r->stepX = -1;
		r->sideDistX = (mlx->posX - r->mapX) * r->deltaDistX;
	}
	else
	{
		r->stepX = 1;
		r->sideDistX = (r->mapX + 1.0 - mlx->posX) * r->deltaDistX;
	}
	if (r->rayDirY < 0)
	{
		r->stepY = -1;
		r->sideDistY = (mlx->posY - r->mapY) * r->deltaDistY;
	}
	else
	{
		r->stepY = 1;
		r->sideDistY = (r->mapY + 1.0 - mlx->posY) * r->deltaDistY;
	}
	r->hit = 0;
	r->hit_type = 0;
	int step_count = 0;
	
	while (r->hit == 0)
	{
		step_count++;
		if (r->sideDistX < r->sideDistY)
		{
			r->sideDistX += r->deltaDistX;
			r->mapX += r->stepX;
			r->side = 0;
		}
		else
		{
			r->sideDistY += r->deltaDistY;
			r->mapY += r->stepY;
			r->side = 1;
		}
		char cell = map->rows[r->mapY][r->mapX];
		
		if (cell == '1')
		{
			r->hit = 1;
			r->hit_type = 1;
		}
		else if (cell == 'D')
		{
			t_door *door = find_door(game, r->mapX, r->mapY);
			if (door && !door->is_open)
			{
				r->hit = 1;
				r->hit_type = 2;
			}
		}
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

void data_update(t_mlx *mlx, t_render *r, t_game *game)
{
	double fov_scale = 1.0;
	double wallX;

	if(r->side == 0) 
		r->perpWallDist = (r->sideDistX - r->deltaDistX);
	else		  
		r->perpWallDist = (r->sideDistY - r->deltaDistY);
	if(r->perpWallDist <= 0.001)
		r->perpWallDist = 0.001;
	r->lineHeight = (int)(screenHeight / r->perpWallDist * fov_scale);
	r->horizon = screenHeight / 2 + mlx->pitch;
	r->drawStart = -r->lineHeight / 2 + r->horizon;
	r->drawEnd = r->lineHeight / 2 + r->horizon;
	if(r->drawStart < 0) r->drawStart = 0;
	if(r->drawEnd >= screenHeight) r->drawEnd = screenHeight - 1;
	if (r->side == 0)
		wallX = mlx->posY + r->perpWallDist * r->rayDirY;
	else
		wallX = mlx->posX + r->perpWallDist * r->rayDirX;
	wallX -= floor(wallX);
	r->texX = (int)(wallX * (double)game->textures.tex_width);
	if (r->side == 0 && r->rayDirX > 0)
		r->texX = game->textures.tex_width - r->texX - 1;
	if (r->side == 1 && r->rayDirY < 0)
		r->texX = game->textures.tex_width - r->texX - 1;
	r->step = 1.0 * game->textures.tex_height / r->lineHeight;
	r->texPos = (r->drawStart - r->horizon + r->lineHeight / 2) * r->step;
	
	r->y = 0;
}

void vertical_update(t_mlx *mlx, t_render *r, t_game *game)
{
	char *texture_data;
	int tex_y;
	int color;
	int y;
	
	// Select texture based on hit type
	if (r->hit_type == 2)  // Door hit
		texture_data = game->textures.data[4];  // Door texture data
	else
		texture_data = get_wall_texture_fast(r, &game->textures);
	
	y = r->drawStart;
	r->texPos = (r->drawStart - r->horizon + r->lineHeight / 2) * r->step;

	while (y <= r->drawEnd)
	{
		tex_y = (int)r->texPos % game->textures.tex_height;
		if (tex_y < 0) tex_y = 0;
		if (tex_y >= game->textures.tex_height) tex_y = game->textures.tex_height - 1;
		r->texPos += r->step;
		color = get_texture_pixel(texture_data, r->texX, tex_y, &game->textures);

		if (r->side == 1)
			color = ((((color >> 16) & 0xFF) * 9 / 10) << 16) | 
					((((color >> 8) & 0xFF) * 9 / 10) << 8) | 
					(((color & 0xFF) * 9 / 10));
		
		if (y >= 0 && y < screenHeight)
			ft_mlx_pixel_put(mlx, r->x, y, color);
		y++;
	}
}

void interact_with_door(t_game *game)
{
	// Check multiple distances to catch doors at any range
	float distances[] = {0.3, 0.6, 0.9, 1.2, 1.5};  // Start closer!
	int num_distances = 5;
	
	for (int i = 0; i < num_distances; i++)
	{
		float check_x = game->mlx.posX + game->mlx.dirX * distances[i];
		float check_y = game->mlx.posY + game->mlx.dirY * distances[i];
		
		int map_x = (int)check_x;
		int map_y = (int)check_y;
		
		// Check bounds
		if (map_x < 0 || map_x >= game->maps.width || 
			map_y < 0 || map_y >= game->maps.height)
			continue;
			
		// Check if there's a door at this position
		if (game->maps.rows[map_y][map_x] == 'D')
		{
			t_door *door = find_door(game, map_x, map_y);
			if (door)
			{
				door->is_open = !door->is_open;
				printf("Door %s at (%d, %d)\n", 
					   door->is_open ? "opened" : "closed", map_x, map_y);
				return; // Exit after first door found
			}
		}
	}
	
	printf("No door found to interact with\n");  // Debug message
}

void render_scene(t_game *game)
{
	t_render r;
	t_mlx *mlx;
	t_map *map;

	map = &game->maps;
	mlx = &game->mlx;
	r.x = 0;
	clear_image(mlx);
	while(r.x < screenWidth)
	{
		render_start(mlx, &r);	 
		apply_dda(mlx, &r, map, game);
		data_update(mlx, &r, game);
		draw_ceiling_floor(mlx, &game->colors, r.x, r.drawStart, r.drawEnd);
		vertical_update(mlx, &r, game);
		mlx->zbuffer[r.x] = r.perpWallDist;
		
		r.x++;
	}
	render_sprites(mlx, &game->sprites);
	draw_minimap(mlx, map, game);
	draw_crosshair(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void check_keycodes(t_mlx *mlx, int keycode, t_game *game)
{
	if (keycode == KEY_W)
		mlx->key_state[0] = 1;
	if (keycode == KEY_A)
		mlx->key_state[1] = 1;
	if (keycode == KEY_S)
		mlx->key_state[2] = 1;
	if (keycode == KEY_D)
		mlx->key_state[3] = 1;
	if (keycode == KEY_SHIFT)
		mlx->key_state[4] = 1;
	if (keycode == KEY_INTERACT)
		interact_with_door(game);
}

int handle_keys(int keycode, t_game *game)
{
	t_mlx *mlx;

	mlx = &game->mlx;
	if (keycode == 65307)
	{
		if (mlx->mouse_locked)
		{
			mlx->mouse_locked = 0;
			mlx_mouse_show(mlx->mlx, mlx->win);
			printf("Mouse unlocked\n");
			return (0);
		}
		exit(0);
	}
	check_keycodes(mlx, keycode, game);
	return (0);
}

int handle_key_release(int keycode, t_game *game)
{
	t_mlx *mlx = &game->mlx;
	
	if (keycode == KEY_W)
		mlx->key_state[0] = 0;
	if (keycode == KEY_A)
		mlx->key_state[1] = 0;
	if (keycode == KEY_S)
		mlx->key_state[2] = 0;
	if (keycode == KEY_D)
		mlx->key_state[3] = 0;
	if (keycode == KEY_SHIFT)
		mlx->key_state[4] = 0;
	return (0);
}

double get_movement_speed(t_mlx *mlx)
{
	if (mlx->key_state[4])
		return MOVE_SPEED * 2.0;
	else
		return MOVE_SPEED;
}

int handle_vertical_movement(t_mlx *mlx, t_map *map, t_game *game)
{
	double current_speed;
	
	current_speed = get_movement_speed(mlx);
	if (mlx->key_state[0])
	{
		if(get_map_value(map, (int)(mlx->posX + mlx->dirX * current_speed), (int)(mlx->posY), game) == 0) 
			mlx->posX += mlx->dirX * current_speed;
		if(get_map_value(map, (int)(mlx->posX), (int)(mlx->posY + mlx->dirY * current_speed), game) == 0) 
			mlx->posY += mlx->dirY * current_speed;
	}
	if (mlx->key_state[2])
	{
		if(get_map_value(map, (int)(mlx->posX - mlx->dirX * current_speed), (int)(mlx->posY), game) == 0) 
			mlx->posX -= mlx->dirX * current_speed;
		if(get_map_value(map, (int)(mlx->posX), (int)(mlx->posY - mlx->dirY * current_speed), game) == 0) 
			mlx->posY -= mlx->dirY * current_speed;
	}
	return (0);
}

int handle_horizontal_movement(t_mlx *mlx, t_map *map, t_game *game)
{
	double current_speed;
	
	current_speed = get_movement_speed(mlx);
	if (mlx->key_state[1])
	{
		if(get_map_value(map, (int)(mlx->posX - mlx->planeX * current_speed), (int)(mlx->posY), game) == 0) 
		mlx->posX -= mlx->planeX * current_speed;
		if(get_map_value(map, (int)(mlx->posX), (int)(mlx->posY - mlx->planeY * current_speed), game) == 0) 
		mlx->posY -= mlx->planeY * current_speed;
	}
	if (mlx->key_state[3])
	{
		if(get_map_value(map, (int)(mlx->posX + mlx->planeX * current_speed), (int)(mlx->posY), game) == 0) 
			mlx->posX += mlx->planeX * current_speed;
		if(get_map_value(map, (int)(mlx->posX), (int)(mlx->posY + mlx->planeY * current_speed), game) == 0) 
			mlx->posY += mlx->planeY * current_speed;
		}
	return (0);
}

void mouse_rotation(t_mouse *mouse, t_mlx *mlx)
{
	if (abs(mouse->delta_x) > 1 || abs(mouse->delta_y) > 1)
	{
		if (abs(mouse->delta_x) > 1)
		{
			mouse->rotation = mouse->delta_x * MOUSE_SENS_X * 0.5;
			mouse->oldDirX = mlx->dirX;
			mlx->dirX = mlx->dirX * cos(mouse->rotation) - mlx->dirY * sin(mouse->rotation);
			mlx->dirY = mouse->oldDirX * sin(mouse->rotation) + mlx->dirY * cos(mouse->rotation);
			mouse->oldPlaneX = mlx->planeX;
			mlx->planeX = mlx->planeX * cos(mouse->rotation) - mlx->planeY * sin(mouse->rotation);
			mlx->planeY = mouse->oldPlaneX * sin(mouse->rotation) + mlx->planeY * cos(mouse->rotation);
		}
		if (abs(mouse->delta_y) > 1)
		{
			mlx->pitch += (-mouse->delta_y) * MOUSE_SENS_Y * 0.5;
			if (mlx->pitch < -320) mlx->pitch = -320;
			if (mlx->pitch > 320) mlx->pitch = 320;
		}
		mlx_mouse_move(mlx->mlx, mlx->win, mouse->center_x, mouse->center_y);
	}
}

int handle_mouse_move(int x, int y, t_mlx *mlx)
{
	t_mouse mouse;
	
	mouse.center_x = screenWidth / 2;
	mouse.center_y = screenHeight / 2;
	mouse.delta_x = x - mouse.center_x;
	mouse.delta_y = y - mouse.center_y;
	if (!mlx->mouse_locked)
		return (0);
	mouse_rotation(&mouse, mlx);
	return (0);
	}

int handle_mouse_press(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;

	if (button == 1)
	{
		if (!mlx->mouse_locked)
		{
			mlx->mouse_locked = 1;
			mlx->last_mouse_x = screenWidth / 2;
			mlx->last_mouse_y = screenHeight / 2;
			mlx_mouse_hide(mlx->mlx, mlx->win);
			mlx_mouse_move(mlx->mlx, mlx->win, mlx->last_mouse_x, mlx->last_mouse_y);
		}
	}
	return (0);
}

int render_loop(t_game *game)
{
	static int frame_count;
	t_mlx *mlx;
	t_map *map;
	
	frame_count = 0;
	mlx = &game->mlx;
	map = &game->maps;
	frame_count++;
	handle_vertical_movement(mlx, map, game);
	handle_horizontal_movement(mlx, map, game);
	render_scene(game);
	
	return (0);
}
void initialize_mlx(t_mlx *mlx)
{
	int i;
	
	i = 0;
	while (i < 10)
	{
		mlx->key_state[i] = 0;
		i++;
	}
	mlx->pitch = 0;
	mlx->last_mouse_x = screenWidth / 2;
	mlx->last_mouse_y = screenHeight / 2;
	mlx->mouse_locked = 0;
	mlx->needs_render = 1;
	mlx->last_render_time = 0;
	mlx->zbuffer = malloc(sizeof(double) * screenWidth);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, screenWidth, screenHeight, "Cub3D Raycasting");
	mlx->img = mlx_new_image(mlx->mlx, screenWidth, screenHeight);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
}

int render_loop_wrapper(void *param)
{
	return render_loop((t_game *)param);
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

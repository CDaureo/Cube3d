/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_testing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:03:24 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/08 21:27:07 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../minilibx-linux/mlx.h"
#include "sys/time.h"
#include "../../includes/cub3d.h"

#define MOVEMENT_FPS 60
#define RENDER_FPS 60
#define TARGET_FPS 60
#define FRAME_TIME_MS (1000 / TARGET_FPS)
//#define screenWidth 1920
//#define screenHeight 1080
#define screenWidth 1280
#define screenHeight 720
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

int get_map_value(t_map *map, int x, int y)
{
	char cell;

	cell = map->rows[y][x];
    if (x < 0 || y < 0 || x >= map->width || y >= map->height)
        return (1);
    if (cell == '1')
        return (1);
    else if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
        return (0);
    else
        return (1);
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

void draw_map_background(t_mlx *mlx, t_minimap *minimap, t_map *map)
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
                if(get_map_value(map, minimap->map_x, minimap->map_y) == 1)
                    minimap->color = 0xFFFFFF;
                else
                    minimap->color = 0x333333;
                minimap->screen_x = minimap->map_start_x + minimap->pixel_x;
                minimap->screen_y = minimap->map_start_y + minimap->pixel_y;
                if(minimap->screen_x < screenWidth && minimap->screen_y < screenHeight)
                    ft_mlx_pixel_put(mlx, minimap->screen_x, minimap->screen_y, minimap->color);
            }
            minimap->pixel_x++;
        }
        minimap->pixel_y++;
    }
}

void draw_arrow_body(t_mlx *mlx, t_minimap *minimap)
{
	minimap->scan_y = -minimap->arrow_length;
	minimap->dx = -minimap->width_at_y;
    while(minimap->scan_y <= minimap->arrow_length)
    {
        if(minimap->scan_y < 0)
            minimap->width_at_y = (minimap->arrow_width * (minimap->arrow_length + minimap->scan_y)) / minimap->arrow_length;
        else
            minimap->width_at_y = minimap->arrow_width;
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
        }
    }
}

void draw_arrow_outline(t_mlx *mlx, t_minimap *minimap)
{
	int i;

	i = 0;
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
    }
}

void draw_player_dot(t_mlx *mlx, t_minimap *minimap)
{
    ft_mlx_pixel_put(mlx, minimap->player_pixel_x, minimap->player_pixel_y, 0xFFFF00);
}

void draw_minimap(t_mlx *mlx, t_map *map)
{
    t_minimap minimap;
    
    init_minimap(&minimap, mlx);
    draw_map_background(mlx, &minimap, map);
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
    t_mlx *mlx = &game->mlx;
    t_textures *tex = &game->textures;
    
    if (!load_texture(mlx, tex->north, &tex->north_img, &tex->north_data, tex))
        return (0);
    if (!load_texture(mlx, tex->south, &tex->south_img, &tex->south_data, tex))
        return (0);
    if (!load_texture(mlx, tex->west, &tex->west_img, &tex->west_data, tex))
        return (0);
    if (!load_texture(mlx, tex->east, &tex->east_img, &tex->east_data, tex))
        return (0);
    
    printf("All textures loaded successfully\n");
    return (1);
}

char *get_wall_texture(t_render *r, t_textures *textures)
{
    if (r->side == 0)
    {
        if (r->stepX > 0)
            return textures->west_data;
        else
            return textures->east_data;
    }
    else
    {
        if (r->stepY > 0)
            return textures->north_data;
        else
            return textures->south_data;
    }
}

int get_texture_pixel(char *texture_data, int tex_x, int tex_y, t_textures *tex)
{
    int pixel_index;

    if (tex_x < 0 || tex_x >= tex->tex_width || tex_y < 0 || tex_y >= tex->tex_height)
        return (0x000000);
    pixel_index = (tex_y * tex->tex_width + tex_x) * 4;
    return (*(int *)(texture_data + pixel_index));
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

	x = -dot_size;
	y = -dot_size;
	while(y <= dot_size)
	{
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
    int center_x;
    int center_y;
    int dot_size;
    int outline_size;
	int pixel_x;
	int pixel_y;
    int y;
	int x;
	
	center_x = screenWidth / 2;
	center_y = screenHeight / 2;
	dot_size = 2;
	outline_size = dot_size + 1;
	y = -outline_size;
	x = -outline_size;
    while(y <= outline_size)
    {
        while(x <= outline_size)
        {
            if(x*x + y*y <= outline_size*outline_size)
            {
                pixel_x = center_x + x;
                pixel_y = center_y + y;
                if(pixel_x >= 0 && pixel_y >= 0 && pixel_x < screenWidth && pixel_y < screenHeight)
                {
                    ft_mlx_pixel_put(mlx, pixel_x, pixel_y, 0x000000);
                }
            }
        }
    }
	draw_dot(mlx, dot_size, center_x, center_y);
}

void initialize_player_from_map(t_mlx *mlx, t_map *map)
{
	double plane_length;
	
    mlx->posX = map->player_x + 0.5;
    mlx->posY = map->player_y + 0.5;
	plane_length = 0.80;
    switch(map->player_dir)
    {
        case 'N':
            mlx->dirX = 0;
            mlx->dirY = -1;
            mlx->planeX = plane_length;
            mlx->planeY = 0;
            break;
        case 'S':
            mlx->dirX = 0;
            mlx->dirY = 1;
            mlx->planeX = -plane_length;
            mlx->planeY = 0;
            break;
        case 'E':
            mlx->dirX = 1;
            mlx->dirY = 0;
            mlx->planeX = 0;
            mlx->planeY = plane_length;
            break;
        case 'W':
            mlx->dirX = -1;
            mlx->dirY = 0;
            mlx->planeX = 0;
            mlx->planeY = -plane_length;
            break;
        default:
            mlx->dirX = -1;
            mlx->dirY = 0;
            mlx->planeX = 0;
            mlx->planeY = -plane_length;
    }
    mlx->pitch = 0;
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

int blend_colors(int original_color, int fog_color, double fog_factor)
{
    int r1 = (original_color >> 16) & 0xFF;
    int g1 = (original_color >> 8) & 0xFF;
    int b1 = original_color & 0xFF;
    
    int r2 = (fog_color >> 16) & 0xFF;
    int g2 = (fog_color >> 8) & 0xFF;
    int b2 = fog_color & 0xFF;
    
    int r = (int)(r1 * (1.0 - fog_factor) + r2 * fog_factor);
    int g = (int)(g1 * (1.0 - fog_factor) + g2 * fog_factor);
    int b = (int)(b1 * (1.0 - fog_factor) + b2 * fog_factor);
    
    return ((r << 16) | (g << 8) | b);
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

void apply_dda(t_mlx *mlx, t_render *r, t_map *map)
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
    while (r->hit == 0)
    {
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
        if (get_map_value(map, r->mapX, r->mapY) == 1)
            r->hit = 1;
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
	int fog_color = 0x202020;
    double fog_distance = r->perpWallDist;
    double fog_start = 2.0;
    double fog_end = 8.0;
    double fog_factor = 0.0;
    
    texture_data = get_wall_texture(r, &game->textures);
    y = r->drawStart;
    r->texPos = (r->drawStart - r->horizon + r->lineHeight / 2) * r->step;
    if (fog_distance > fog_start) 
    {
        fog_factor = (fog_distance - fog_start) / (fog_end - fog_start);
        if (fog_factor > 1.0) fog_factor = 1.0;
        fog_factor = fog_factor * fog_factor;
    }
    while (y <= r->drawEnd)
    {
        tex_y = (int)r->texPos % game->textures.tex_height;
        if (tex_y < 0) tex_y = 0;
        if (tex_y >= game->textures.tex_height) tex_y = game->textures.tex_height - 1;
        r->texPos += r->step;
        color = get_texture_pixel(texture_data, r->texX, tex_y, &game->textures);
        if (fog_distance > 1.0)
        {
            color = blend_colors(color, fog_color, fog_factor);
        }
        color = apply_vignette(color, r->x, y);
        if (y >= 0 && y < screenHeight)
            ft_mlx_pixel_put(mlx, r->x, y, color);
        y++;
    }
}

void render_scene(t_game *game)
{
    t_render r;
    t_mlx *mlx = &game->mlx;
    t_map *map = &game->maps;

    r.x = 0;
    clear_image(mlx);
    
    while(r.x < screenWidth)
    {
        render_start(mlx, &r);
        apply_dda(mlx, &r, map);
        data_update(mlx, &r, game);
        draw_ceiling_floor(mlx, &game->colors, r.x, r.drawStart, r.drawEnd);
        vertical_update(mlx, &r, game);
        r.x++;
    }
    draw_minimap(mlx, map);
    draw_crosshair(mlx);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int handle_keys(int keycode, t_mlx *mlx)
{
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
    return (0);
}

int handle_key_release(int keycode, t_mlx *mlx)
{
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

int handle_vertical_movement(t_mlx *mlx, t_map *map)
{
	double current_speed = get_movement_speed(mlx);
	
    if (mlx->key_state[0])
    {
		if(get_map_value(map, (int)(mlx->posX + mlx->dirX * current_speed), (int)(mlx->posY)) == 0) 
		mlx->posX += mlx->dirX * current_speed;
        if(get_map_value(map, (int)(mlx->posX), (int)(mlx->posY + mlx->dirY * current_speed)) == 0) 
		mlx->posY += mlx->dirY * current_speed;
    }
    if (mlx->key_state[2])
    {
		if(get_map_value(map, (int)(mlx->posX - mlx->dirX * current_speed), (int)(mlx->posY)) == 0) 
            mlx->posX -= mlx->dirX * current_speed;
        if(get_map_value(map, (int)(mlx->posX), (int)(mlx->posY - mlx->dirY * current_speed)) == 0) 
            mlx->posY -= mlx->dirY * current_speed;
    }
    return (0);
}

int handle_horizontal_movement(t_mlx *mlx, t_map *map)
{
	double current_speed = get_movement_speed(mlx);
	
    if (mlx->key_state[1])
    {
		if(get_map_value(map, (int)(mlx->posX - mlx->planeX * current_speed), (int)(mlx->posY)) == 0) 
		mlx->posX -= mlx->planeX * current_speed;
        if(get_map_value(map, (int)(mlx->posX), (int)(mlx->posY - mlx->planeY * current_speed)) == 0) 
		mlx->posY -= mlx->planeY * current_speed;
    }
    if (mlx->key_state[3])
    {
        if(get_map_value(map, (int)(mlx->posX + mlx->planeX * current_speed), (int)(mlx->posY)) == 0) 
            mlx->posX += mlx->planeX * current_speed;
        if(get_map_value(map, (int)(mlx->posX), (int)(mlx->posY + mlx->planeY * current_speed)) == 0) 
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
    t_mlx *mlx = &game->mlx;
    t_map *map = &game->maps;

    handle_vertical_movement(mlx, map);
    handle_horizontal_movement(mlx, map);
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
    mlx->mlx = mlx_init();
    mlx->win = mlx_new_window(mlx->mlx, screenWidth, screenHeight, "Cub3D Raycasting");
    mlx->img = mlx_new_image(mlx->mlx, screenWidth, screenHeight);
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
}

int render_loop_wrapper(void *param)
{
    return render_loop((t_game *)param);
}

int main(int argc, char **argv)
{
    t_game game;
    
    if (argc != 2)
        return (printf("Usage: %s <map.cub>\n", argv[0]), 1);
    memset(&game, 0, sizeof(t_game));
    if (!parse_file(argv[1], &game))
        return (printf("Error: Failed to parse map file\n"), 1);
    initialize_mlx(&game.mlx);
    if (!load_all_textures(&game))
        return (printf("Error: Failed to load textures\n"), 1);
    initialize_player_from_map(&game.mlx, &game.maps);
    mlx_hook(game.mlx.win, 2, 1L << 0, handle_keys, &game.mlx);
    mlx_hook(game.mlx.win, 3, 1L << 1, handle_key_release, &game.mlx);
    mlx_hook(game.mlx.win, 4, 1L << 2, handle_mouse_press, &game.mlx);
    mlx_hook(game.mlx.win, 6, 1L << 6, handle_mouse_move, &game.mlx);
    mlx_hook(game.mlx.win, 17, 0, close_hook, &game.mlx);
    mlx_loop_hook(game.mlx.mlx, render_loop_wrapper, &game);
    mlx_loop(game.mlx.mlx);
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_testing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:03:24 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/03 18:37:18 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../minilibx-linux/mlx.h"
#include "sys/time.h"

#define TARGET_FPS 60
#define FRAME_TIME_MS (1000 / TARGET_FPS)
#define screenWidth 1280
#define screenHeight 720
#define mapWidth 48
#define mapHeight 48
#define MOVE_SPEED 0.00005
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


// Replace your worldMap with this corrected version:
int worldMap[mapWidth][mapHeight]=
{
  // Outer walls (rows 0-9: top border and open area)
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  
  // First maze section (rows 10-23)
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  
  // Large horizontal corridor (rows 24-27)
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  
  // Complex maze section (rows 28-38)
  {1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1},
  {1,0,0,1,0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1},
  {1,0,0,1,0,0,1,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
  
  // Open area with scattered pillars (rows 39-46)
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,1},
  {1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1},
  {1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  
  // Final outer wall (row 47)
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct s_mouse {
	int center_x ;
    int center_y;
    int delta_x;
    int delta_y ;
	double rotation;
	double oldDirX;
	double oldPlaneX;
}	t_mouse;

// Color structure for C
typedef struct s_color {
    int r;
	int g; 
	int b;
} t_color;

// Define colors
t_color NORTH_WALL = {255, 0, 0};     // Red for North walls
t_color SOUTH_WALL = {0, 255, 0};     // Green for South walls  
t_color EAST_WALL = {0, 0, 255};      // Blue for East walls
t_color WEST_WALL = {255, 255, 0};    // Yellow for West walls

// Function to darken color (divide by 2)
t_color darken_color(t_color color)
{
    t_color dark;
    dark.r = color->r / 2;
    dark.g = color->g / 2;
    dark.b = color->b / 2;
    return dark;
}

typedef struct s_minimap {
    // Basic positioning
    int map_start_x;
    int map_start_y;
    int center_x;
    int center_y;
    int radius;
    int player_pixel_x;
    int player_pixel_y;
    double player_angle;
    int arrow_length;
    int arrow_width;
    
    // Map background variables
    double rel_x;
    double rel_y;
    double rotated_x;
    double rotated_y;
    double world_x;
    double world_y;
    int map_x;
    int map_y;
    int color;
    int pixel_x;
    int pixel_y;
    int dx;
    int dy;
    int distance_squared;
    int screen_x;
    int screen_y;
    
    // Arrow outline variables
    int tip_x;
    int tip_y;
    int base_center_x;
    int base_center_y;
    int base_left_x;
    int base_left_y;
    int base_right_x;
    int base_right_y;
    int lx1;
    int ly1;
    int lx2;
    int ly2;
    int lx3;
    int ly3;
    int outline_dx;
    int outline_dy;
    int outline_dx1;
    int outline_dy1;
    int outline_dx2;
    int outline_dy2;
    
    // Arrow body variables
    int scan_y;
    int width_at_y;
    int current_x;
    int current_y_adj;
    int arrow_dx;
    int arrow_dy;
    
    // Circle variables
    int angle;
    double radian;
    int border_x;
    int border_y;
    int inner_border_x;
    int inner_border_y;
} t_minimap;

typedef struct s_mlx {
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    int key_state[10];
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
	double pitch;
	int last_mouse_x;
    int last_mouse_y;
    int mouse_locked;
    int needs_render;
    long last_render_time;
} t_mlx;

typedef struct s_render {
	double cameraX;
	double rayDirX;
	double rayDirY;
	double sideDistX;
    double sideDistY;
	double deltaDistY;
	double deltaDistX;
    double perpWallDist;
	int drawStart;
	int drawEnd;
	int horizon;
	int lineHeight;
	int mapX;
	int mapY;
	int stepX;
    int stepY;
    int hit;
    int side;
    int x;
	int y;
} t_render;

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
//Esto hay que arreglarlo
void init_minimap(t_minimap *minimap, t_mlx *mlx)
{
    minimap->map_start_x = screenWidth - MINIMAP_SIZE - MINIMAP_OFFSET;
    minimap->map_start_y = screenHeight - MINIMAP_SIZE - MINIMAP_OFFSET;
    minimap->center_x = minimap->map_start_x + MINIMAP_SIZE / 2;
    minimap->center_y = minimap->map_start_y + MINIMAP_SIZE / 2;
    minimap->radius = MINIMAP_SIZE / 2;
    minimap->player_pixel_x = minimap->center_x;
    minimap->player_pixel_y = minimap->center_y;
    minimap->player_angle = atan2(mlx->dirY, mlx->dirX) - M_PI/2;
    minimap->arrow_length = 6;
    minimap->arrow_width = 4;
}

// Updated minimap functions with structure:
void draw_map_background(t_mlx *mlx, t_minimap *minimap)
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
                minimap->rel_y = -minimap->dy / (double)(MINIMAP_SIZE / 2);
                minimap->rotated_x = minimap->rel_x * cos(minimap->player_angle) - minimap->rel_y * sin(minimap->player_angle);
                minimap->rotated_y = minimap->rel_x * sin(minimap->player_angle) + minimap->rel_y * cos(minimap->player_angle);
                minimap->world_x = mlx->posX + minimap->rotated_x * (mapWidth * 0.3);   
                minimap->world_y = mlx->posY + minimap->rotated_y * (mapHeight * 0.3);  
                minimap->map_x = (int)minimap->world_x;
                minimap->map_y = (int)minimap->world_y;
                
                if(minimap->map_x >= 0 && minimap->map_x < mapWidth && minimap->map_y >= 0 && minimap->map_y < mapHeight)
                {
                    if(worldMap[minimap->map_x][minimap->map_y] == 1)
                        minimap->color = 0xFFFFFF;
                    else
                        minimap->color = 0x333333;
                }
                else
                    minimap->color = 0xFFFFFF;
                    
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
    for(minimap->scan_y = -minimap->arrow_length; minimap->scan_y <= minimap->arrow_length; minimap->scan_y++)
    {
        if(minimap->scan_y < 0)
            minimap->width_at_y = (minimap->arrow_width * (minimap->arrow_length + minimap->scan_y)) / minimap->arrow_length;
        else
            minimap->width_at_y = minimap->arrow_width;
            
        for(minimap->dx = -minimap->width_at_y; minimap->dx <= minimap->width_at_y; minimap->dx++)
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
    minimap->tip_x = minimap->player_pixel_x;
    minimap->tip_y = minimap->player_pixel_y - minimap->arrow_length;
    minimap->base_center_x = minimap->player_pixel_x;
    minimap->base_center_y = minimap->player_pixel_y + minimap->arrow_length;
    minimap->base_left_x = minimap->base_center_x - minimap->arrow_width;
    minimap->base_left_y = minimap->base_center_y;
    minimap->base_right_x = minimap->base_center_x + minimap->arrow_width;
    minimap->base_right_y = minimap->base_center_y;
    
    for(int i = 0; i <= 20; i++)
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
    for(minimap->angle = 0; minimap->angle < 360; minimap->angle++)
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

// Updated main minimap function:
void draw_minimap(t_mlx *mlx)
{
    t_minimap minimap;
    
    init_minimap(&minimap, mlx);
    draw_map_background(mlx, &minimap);
    draw_arrow_body(mlx, &minimap);
    draw_arrow_outline(mlx, &minimap);
    draw_player_dot(mlx, &minimap);
    draw_minimap_circle(mlx, &minimap);
}

t_color get_wall_color(int side, int stepX, int stepY)
{
    if (side == 0)
    {
        if (stepX > 0)
            return WEST_WALL;
        else
            return EAST_WALL;
    }
    else
    {
        if (stepY > 0)
            return NORTH_WALL;
        else
            return SOUTH_WALL;
    }
}

void draw_vertical_line(t_mlx *mlx, int x, int start, int end, t_color color)
{
    int rgb_color;
    int	draw_start;
	int draw_end;
	int y;

    rgb_color = (color->r << 16) | (color->g << 8) | color->b;
    draw_start = start < 0 ? 0 : start;
    draw_end = end >= screenHeight ? screenHeight - 1 : end;
	y = draw_start;
    while(y <= draw_end)
    {
        if(y >= 0 && y < screenHeight)
            ft_mlx_pixel_put(mlx, x, y, rgb_color);
		y++;
    }
}

int key_hook(int keycode, t_mlx *mlx)
{
    if(keycode == 65307)
        exit(0);
    return (0);
}

int close_hook(t_mlx *mlx)
{
    exit(0);
}

static void clear_image(t_mlx *data)
{
    int x;
    int y;
    char *dst;

	x = 0;
	y = 0;
    while (y < screenHeight)
    {
        x = 0;
        while (x < screenWidth)
        {
            dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
            *(unsigned int *)dst = 0x000000;
            x++;
        }
        y++;
    }
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
    int center_x = screenWidth / 2;
    int center_y = screenHeight / 2;
    int dot_size = 2;
    int outline_size = dot_size + 1;
    
    for(int y = -outline_size; y <= outline_size; y++)
    {
        for(int x = -outline_size; x <= outline_size; x++)
        {
            if(x*x + y*y <= outline_size*outline_size)
            {
                int pixel_x = center_x + x;
                int pixel_y = center_y + y;
                if(pixel_x >= 0 && pixel_y >= 0 && pixel_x < screenWidth && pixel_y < screenHeight)
                {
                    ft_mlx_pixel_put(mlx, pixel_x, pixel_y, 0x000000);
                }
            }
        }
    }
	draw_dot(mlx, dot_size, center_x, center_y);
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

void apply_dda(t_mlx *mlx, t_render *r)
{
	if(r->rayDirX < 0)
        {
            r->stepX = -1;
            r->sideDistX = (mlx->posX - r->mapX) * r->deltaDistX;
        }
        else
        {
            r->stepX = 1;
            r->sideDistX = (r->mapX + 1.0 - mlx->posX) * r->deltaDistX;
        }
        if(r->rayDirY < 0)
        {
            r->stepY = -1;
            r->sideDistY = (mlx->posY - r->mapY) * r->deltaDistY;
        }
        else
        {
            r->stepY = 1;
            r->sideDistY = (r->mapY + 1.0 - mlx->posY) * r->deltaDistY;
        }
}

void hit_check(t_mlx *mlx, t_render *r)
{
	while(r->hit == 0)
	{
		if(r->sideDistX < r->sideDistY)
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
		if(worldMap[r->mapX][r->mapY] == 1) r->hit = 1;
	}
}

void data_update(t_mlx *mlx, t_render *r, t_color *color)
{
	if(r->side == 0) 
		r->perpWallDist = (r->sideDistX - r->deltaDistX);
	else          
		r->perpWallDist = (r->sideDistY - r->deltaDistY);
	if(r->perpWallDist <= 0.001)
		r->perpWallDist = 0.001;
	r->lineHeight = (int)(screenHeight / r->perpWallDist);
	r->horizon = screenHeight / 2 + mlx->pitch;
	r->drawStart = -r->lineHeight / 2 + r->horizon;
	r->drawEnd = r->lineHeight / 2 + r->horizon;
	if(r->drawStart < 0) r->drawStart = 0;
	if(r->drawEnd >= screenHeight) r->drawEnd = screenHeight - 1;
	*color = get_wall_color(r->side, r->stepX, r->stepY);
	if(r->side == 1) 
		*color = darken_color(*color);
	r->y = 0;
}

void vertical_update(t_mlx *mlx, t_render *r, t_color *color)
{
	while(r->y < r->drawStart)
	{
		if(r->y >= 0)
			ft_mlx_pixel_put(mlx, r->x, r->y, 0x87CEEB);
		r->y++;
	}
	draw_vertical_line(mlx, r->x, r->drawStart, r->drawEnd, *color);
	r->y = (r->drawEnd + 1 > 0 ? r->drawEnd + 1 : 0);
	while(r->y < screenHeight)
	{
		ft_mlx_pixel_put(mlx, r->x, r->y, 0x8B4513);
		r->y++;
	}
}

void render_scene(t_mlx *mlx, t_render *r)
{
	t_color color;

	r->x = 0;
    clear_image(mlx);
    while(r->x < screenWidth)
    {
		render_start(&mlx, &r);
		apply_dda(&mlx, &r);
		hit_check(&mlx, &r);
		data_update(&mlx, &r, &color);
		vertical_update(&mlx, &r, &color);
		r->x++;
    }
    draw_minimap(mlx);
	draw_crosshair(mlx);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int handle_keys(int keycode, t_mlx *mlx)
{
    if (keycode == 65307) // ESC
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

int handle_vertical_movement(t_mlx *mlx)
{
    double current_speed;

	current_speed = get_movement_speed(mlx);
    if (mlx->key_state[0])
    {
        if(worldMap[(int)(mlx->posX + mlx->dirX * current_speed)][(int)(mlx->posY)] != 1) 
            mlx->posX += mlx->dirX * current_speed;
        if(worldMap[(int)(mlx->posX)][(int)(mlx->posY + mlx->dirY * current_speed)] != 1) 
            mlx->posY += mlx->dirY * current_speed;
        return (1);
    }
    if (mlx->key_state[2])
    {
        if(worldMap[(int)(mlx->posX - mlx->dirX * current_speed)][(int)(mlx->posY)] != 1) 
            mlx->posX -= mlx->dirX * current_speed;
        if(worldMap[(int)(mlx->posX)][(int)(mlx->posY - mlx->dirY * current_speed)] != 1) 
            mlx->posY -= mlx->dirY * current_speed;
        return (1);
    }
    return (0);
}

int handle_horizontal_movement(t_mlx *mlx)
{
    double current_speed;
    
	current_speed = get_movement_speed(mlx);
    if (mlx->key_state[1])
    {
        if(worldMap[(int)(mlx->posX - mlx->planeX * current_speed)][(int)(mlx->posY)] != 1) 
            mlx->posX -= mlx->planeX * current_speed;
        if(worldMap[(int)(mlx->posX)][(int)(mlx->posY - mlx->planeY * current_speed)] != 1) 
            mlx->posY -= mlx->planeY * current_speed;
    }
    if (mlx->key_state[3])
    {
        if(worldMap[(int)(mlx->posX + mlx->planeX * current_speed)][(int)(mlx->posY)] != 1) 
            mlx->posX += mlx->planeX * current_speed;
        if(worldMap[(int)(mlx->posX)][(int)(mlx->posY + mlx->planeY * current_speed)] != 1) 
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
        	mouse->rotation = -mouse->delta_x * MOUSE_SENS_X * 0.5;
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
	mouse_rotation(&mouse, &mlx);
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

int render_loop(t_mlx *mlx)
{
	long current_time;

	current_time = get_time_ms();
    handle_vertical_movement(mlx);
	handle_horizontal_movement(mlx);
    if ((current_time - mlx->last_render_time) >= FRAME_TIME_MS)
    {
        render_scene(mlx);
        mlx->last_render_time = current_time;
    }
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
    mlx->posX = 40;
    mlx->posY = 24;
    mlx->dirX = -1;
    mlx->dirY = 0;
    mlx->planeX = 0;
    mlx->planeY = 0.66;
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

int main(void)
{
    t_mlx mlx;
    int i = 0;

	initialize_mlx(&mlx);
    mlx_hook(mlx.win, 2, 1L << 0, handle_keys, &mlx);
    mlx_hook(mlx.win, 3, 1L << 1, handle_key_release, &mlx);
    mlx_hook(mlx.win, 4, 1L << 2, handle_mouse_press, &mlx);
    mlx_hook(mlx.win, 6, 1L << 6, handle_mouse_move, &mlx);
    mlx_loop_hook(mlx.mlx, render_loop, &mlx);
    mlx_hook(mlx.win, 17, 0, close_hook, &mlx);
    render_scene(&mlx);
    mlx_loop(mlx.mlx);
    return (0);
}

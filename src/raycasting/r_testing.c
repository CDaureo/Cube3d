/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_testing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:03:24 by simgarci          #+#    #+#             */
/*   Updated: 2026/01/29 16:47:34 by simgarci         ###   ########.fr       */
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


// Color structure for C
typedef struct s_color {
    int r, g, b;
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
    dark.r = color.r / 2;
    dark.g = color.g / 2;
    dark.b = color.b / 2;
    return dark;
}

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
void draw_minimap(t_mlx *mlx)
{
    // Calculate minimap position (bottom-right corner)
    int map_start_x = screenWidth - MINIMAP_SIZE - MINIMAP_OFFSET;
    int map_start_y = screenHeight - MINIMAP_SIZE - MINIMAP_OFFSET;
    
    // Calculate center and radius for circular minimap
    int center_x = map_start_x + MINIMAP_SIZE / 2;
    int center_y = map_start_y + MINIMAP_SIZE / 2;
    int radius = MINIMAP_SIZE / 2;
    
    // Player is always at the center of the minimap
    int player_pixel_x = center_x;
    int player_pixel_y = center_y;
    
    // FIXED: Calculate rotation angle correctly for forward direction
    double player_angle = atan2(mlx->dirY, mlx->dirX) - M_PI/2; // Subtract 90 degrees to make forward point up
    
    // Draw the map - The map rotates so forward is always "up"
    for(int pixel_y = 0; pixel_y < MINIMAP_SIZE; pixel_y++)
    {
        for(int pixel_x = 0; pixel_x < MINIMAP_SIZE; pixel_x++)
        {
            // Calculate distance from center
            int dx = pixel_x - MINIMAP_SIZE / 2;
            int dy = pixel_y - MINIMAP_SIZE / 2;
            int distance_squared = dx * dx + dy * dy;
            
            // Only draw if pixel is inside the circle
            if(distance_squared <= radius * radius)
            {
                // Convert screen pixel to relative coordinates from center
                double rel_x = dx / (double)(MINIMAP_SIZE / 2);
                double rel_y = -dy / (double)(MINIMAP_SIZE / 2);
                
                // FIXED: Rotate coordinates so that player's forward direction points up
                double rotated_x = rel_x * cos(player_angle) - rel_y * sin(player_angle);
                double rotated_y = rel_x * sin(player_angle) + rel_y * cos(player_angle);
                
                // FIXED: Scale and translate to world coordinates
                double world_x = mlx->posX + rotated_x * (mapWidth * 0.3);   
                double world_y = mlx->posY + rotated_y * (mapHeight * 0.3);  
                
                int map_x = (int)world_x;
                int map_y = (int)world_y;
                
                // Choose color based on map cell or out-of-bounds
                int color;
                if(map_x >= 0 && map_x < mapWidth && map_y >= 0 && map_y < mapHeight)
                {
                    // We're inside the map bounds
                    if(worldMap[map_x][map_y] == 1)
                        color = 0xFFFFFF;  // White for walls
                    else
                        color = 0x333333;  // Dark gray for empty space
                }
                else
                {
                    // We're outside the map bounds - show as wall (white)
                    color = 0xFFFFFF;  // White for out-of-bounds (like walls)
                }
                
                // Draw the pixel directly
                int screen_x = map_start_x + pixel_x;
                int screen_y = map_start_y + pixel_y;
                
                if(screen_x < screenWidth && screen_y < screenHeight)
                    ft_mlx_pixel_put(mlx, screen_x, screen_y, color);
            }
        }
    }
    
    // Draw player arrow - ALWAYS POINTING UP (forward direction on minimap)
    // Arrow parameters - GPS style (centered on player, always pointing up)
    int arrow_length = 6;    // Half length from center to tip
    int arrow_width = 4;     // Half width of arrow base
    
    // Arrow always points up on the minimap (which represents forward direction)
    double arrow_dirX = 0;   // No horizontal component
    double arrow_dirY = -1;  // Always pointing up (negative Y is up on screen)
    
    // Calculate arrow points (all relative to player center)
    // Tip point (upward from center)
    int tip_x = player_pixel_x + (int)(arrow_dirX * arrow_length);
    int tip_y = player_pixel_y + (int)(arrow_dirY * arrow_length);
    
    // Base points (downward from center)
    int base_center_x = player_pixel_x - (int)(arrow_dirX * arrow_length);
    int base_center_y = player_pixel_y - (int)(arrow_dirY * arrow_length);
    
    // Calculate perpendicular vector for arrow width (horizontal)
    double perpX = 1;   // Perpendicular is horizontal
    double perpY = 0;   // No vertical component for width
    
    // Left and right base points
    int base_left_x = base_center_x - (int)(perpX * arrow_width);  // Left side
    int base_left_y = base_center_y + (int)(perpY * arrow_width);
    int base_right_x = base_center_x + (int)(perpX * arrow_width); // Right side
    int base_right_y = base_center_y - (int)(perpY * arrow_width);
    
    // Fill the arrow using scanline method (only if inside circle)
    for(int scan_y = -arrow_length; scan_y <= arrow_length; scan_y++)
    {
        // Calculate the width at this scanline
        int width_at_y;
        if(scan_y < 0) // We're in the tip part (triangle) - negative because pointing up
        {
            // Linear interpolation from full width to 0
            width_at_y = (arrow_width * (arrow_length + scan_y)) / arrow_length;
        }
        else // We're in the base part (rectangle)
        {
            width_at_y = arrow_width;
        }
        
        // Draw the horizontal line at this y position
        for(int dx = -width_at_y; dx <= width_at_y; dx++)
        {
            int current_x = player_pixel_x + dx;  // Just horizontal offset
            int current_y_adj = player_pixel_y + scan_y;  // Vertical position
            
            // Check if arrow pixel is inside the circular minimap
            int arrow_dx = current_x - center_x;
            int arrow_dy = current_y_adj - center_y;
            if(arrow_dx * arrow_dx + arrow_dy * arrow_dy <= radius * radius)
            {
                if(current_x >= 0 && current_y_adj >= 0 && current_x < screenWidth && current_y_adj < screenHeight)
                    ft_mlx_pixel_put(mlx, current_x, current_y_adj, 0xFF0000);  // Red filled arrow
            }
        }
    }
    
    // Draw arrow outline for better visibility (only if inside circle)
    for(int i = 0; i <= 20; i++)
    {
        // Left edge (base to tip)
        int lx1 = base_left_x + (int)((tip_x - base_left_x) * i / 20.0);
        int ly1 = base_left_y + (int)((tip_y - base_left_y) * i / 20.0);
        
        // Right edge (base to tip)
        int lx2 = base_right_x + (int)((tip_x - base_right_x) * i / 20.0);
        int ly2 = base_right_y + (int)((tip_y - base_right_y) * i / 20.0);
        
        // Base edge (left to right)
        if(i <= 10) // Only draw base for first half
        {
            int lx3 = base_left_x + (int)((base_right_x - base_left_x) * i / 10.0);
            int ly3 = base_left_y + (int)((base_right_y - base_left_y) * i / 10.0);
            
            // Check if outline pixel is inside circle
            int outline_dx = lx3 - center_x;
            int outline_dy = ly3 - center_y;
            if(outline_dx * outline_dx + outline_dy * outline_dy <= radius * radius)
            {
                if(lx3 >= 0 && ly3 >= 0 && lx3 < screenWidth && ly3 < screenHeight)
                    ft_mlx_pixel_put(mlx, lx3, ly3, 0xFFFFFF);  // White outline
            }
        }
        
        // Check if outline pixels are inside circle
        int outline_dx1 = lx1 - center_x;
        int outline_dy1 = ly1 - center_y;
        int outline_dx2 = lx2 - center_x;
        int outline_dy2 = ly2 - center_y;
        
        if(outline_dx1 * outline_dx1 + outline_dy1 * outline_dy1 <= radius * radius)
        {
            if(lx1 >= 0 && ly1 >= 0 && lx1 < screenWidth && ly1 < screenHeight)
                ft_mlx_pixel_put(mlx, lx1, ly1, 0xFFFFFF);  // White outline
        }
        
        if(outline_dx2 * outline_dx2 + outline_dy2 * outline_dy2 <= radius * radius)
        {
            if(lx2 >= 0 && ly2 >= 0 && lx2 < screenWidth && ly2 < screenHeight)
                ft_mlx_pixel_put(mlx, lx2, ly2, 0xFFFFFF);  // White outline
        }
    }
    
    // Draw player center dot (always at minimap center now)
    ft_mlx_pixel_put(mlx, player_pixel_x, player_pixel_y, 0xFFFF00);  // Yellow center
    
    // Draw circular border
    for(int angle = 0; angle < 360; angle++)
    {
        double radian = angle * M_PI / 180.0;
        int border_x = center_x + (int)(cos(radian) * radius);
        int border_y = center_y + (int)(sin(radian) * radius);
        
        if(border_x >= 0 && border_y >= 0 && border_x < screenWidth && border_y < screenHeight)
            ft_mlx_pixel_put(mlx, border_x, border_y, 0xFFFFFF);  // White circular border
        
        // Draw a slightly thicker border
        int inner_border_x = center_x + (int)(cos(radian) * (radius - 1));
        int inner_border_y = center_y + (int)(sin(radian) * (radius - 1));
        
        if(inner_border_x >= 0 && inner_border_y >= 0 && inner_border_x < screenWidth && inner_border_y < screenHeight)
            ft_mlx_pixel_put(mlx, inner_border_x, inner_border_y, 0xFFFFFF);
    }
}
t_color get_wall_color(int side, int stepX, int stepY)
{
    if (side == 0) // We hit a vertical wall (X-direction)
    {
        if (stepX > 0) // Moving in positive X direction, hit west side of wall
            return WEST_WALL;
        else           // Moving in negative X direction, hit east side of wall
            return EAST_WALL;
    }
    else // We hit a horizontal wall (Y-direction) 
    {
        if (stepY > 0) // Moving in positive Y direction, hit north side of wall
            return NORTH_WALL;
        else           // Moving in negative Y direction, hit south side of wall
            return SOUTH_WALL;
    }
}

void draw_vertical_line(t_mlx *mlx, int x, int start, int end, t_color color)
{
    int rgb_color;
    int	draw_start;
	int draw_end;
	int y;

    rgb_color = (color.r << 16) | (color.g << 8) | color.b;
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

void render_scene(t_mlx *mlx)
{
    clear_image(mlx);
    
    int x;
    for(x = 0; x < screenWidth; x++)
    {
        // ... existing raycasting code remains the same ...
        
        // Calculate ray position and direction
        double cameraX = 2 * x / (double)screenWidth - 1;
        double rayDirX = mlx->dirX + mlx->planeX * cameraX;
        double rayDirY = mlx->dirY + mlx->planeY * cameraX;
        
        // Which box of the map we're in
        int mapX = (int)mlx->posX;
        int mapY = (int)mlx->posY;

        double sideDistX;
        double sideDistY;
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;
        int hit = 0;
        int side;
        
        // Calculate step and initial sideDist
        if(rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (mlx->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - mlx->posX) * deltaDistX;
        }
        if(rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (mlx->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - mlx->posY) * deltaDistY;
        }
        
        // Perform DDA
        while(hit == 0)
        {
            if(sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            // Check for wall (1 means wall)
            if(worldMap[mapX][mapY] == 1) hit = 1;
        }
        
        // Calculate distance
        if(side == 0) 
            perpWallDist = (sideDistX - deltaDistX);
        else          
            perpWallDist = (sideDistY - deltaDistY);

        // Add bounds checking to prevent overflow
        if(perpWallDist <= 0.001)
            perpWallDist = 0.001;
        
        int lineHeight = (int)(screenHeight / perpWallDist);
        
        // Apply pitch offset to wall position
        int horizon = screenHeight / 2 + mlx->pitch;
        int drawStart = -lineHeight / 2 + horizon;
        int drawEnd = lineHeight / 2 + horizon;
        
        // Bounds checking
        if(drawStart < 0) drawStart = 0;
        if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        // Get wall color based on direction
        t_color color = get_wall_color(side, stepX, stepY);

        // Optional: Make some sides darker for better depth perception
        if(side == 1) 
            color = darken_color(color);
        
        // Draw ceiling (adjusted for pitch)
        for(int y = 0; y < drawStart && y < screenHeight; y++)
        {
            if(y >= 0)  // Only draw if on screen
                ft_mlx_pixel_put(mlx, x, y, 0x87CEEB);
        }
        // Draw wall
        draw_vertical_line(mlx, x, drawStart, drawEnd, color);
        
        // Draw floor (adjusted for pitch)
        for(int y = (drawEnd + 1 > 0 ? drawEnd + 1 : 0); y < screenHeight; y++)
        {
            ft_mlx_pixel_put(mlx, x, y, 0x8B4513);
        }
    }

    // Add minimap after all the 3D rendering
    draw_minimap(mlx);

	draw_crosshair(mlx);

    // Display the image
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
    if (keycode == KEY_SHIFT)  // Add shift key release
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
    double current_speed = get_movement_speed(mlx);
    
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
	double current_speed = get_movement_speed(mlx);

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

int handle_mouse_move(int x, int y, t_mlx *mlx)
{
    int center_x = screenWidth / 2;
    int center_y = screenHeight / 2;

    if (!mlx->mouse_locked)
        return (0);
    int delta_x = x - center_x;
    int delta_y = y - center_y;
    if (abs(delta_x) > 1 || abs(delta_y) > 1)
    {
        if (abs(delta_x) > 1)
        {
            double rotation = -delta_x * MOUSE_SENS_X * 0.5;  // Reduced sensitivity
            double oldDirX = mlx->dirX;
            mlx->dirX = mlx->dirX * cos(rotation) - mlx->dirY * sin(rotation);
            mlx->dirY = oldDirX * sin(rotation) + mlx->dirY * cos(rotation);
            double oldPlaneX = mlx->planeX;
            mlx->planeX = mlx->planeX * cos(rotation) - mlx->planeY * sin(rotation);
            mlx->planeY = oldPlaneX * sin(rotation) + mlx->planeY * cos(rotation);
        }
        if (abs(delta_y) > 1)
        {
            mlx->pitch += (-delta_y) * MOUSE_SENS_Y * 0.5;  // Reduced sensitivity
            if (mlx->pitch < -320) mlx->pitch = -320;
            if (mlx->pitch > 320) mlx->pitch = 320;
        }
        mlx_mouse_move(mlx->mlx, mlx->win, center_x, center_y);
    }
    return (0);
}

int handle_mouse_press(int button, int x, int y, t_mlx *mlx)
{
    (void)x;
    (void)y;
    
    if (button == 1) // Left mouse button
    {
        if (!mlx->mouse_locked)
        {
            // Lock mouse to center of window
            mlx->mouse_locked = 1;
            mlx->last_mouse_x = screenWidth / 2;
            mlx->last_mouse_y = screenHeight / 2;
            // Hide cursor and warp to center
            mlx_mouse_hide(mlx->mlx, mlx->win);
            mlx_mouse_move(mlx->mlx, mlx->win, mlx->last_mouse_x, mlx->last_mouse_y);
        }
    }
    return (0);
}

int render_loop(t_mlx *mlx)
{
    handle_vertical_movement(mlx);
	handle_horizontal_movement(mlx);
    long current_time = get_time_ms();
    if ((current_time - mlx->last_render_time) >= FRAME_TIME_MS)
    {
        render_scene(mlx);
        mlx->last_render_time = current_time;
    }
    return (0);
}

int main(void)
{
    t_mlx mlx;
    int i = 0;
    
    while (i < 10)
    {
        mlx.key_state[i] = 0;
        i++;
    }
    mlx.posX = 40;
    mlx.posY = 24;
    mlx.dirX = -1;
    mlx.dirY = 0;
    mlx.planeX = 0;
    mlx.planeY = 0.66;
    mlx.pitch = 0;
    mlx.last_mouse_x = screenWidth / 2;
    mlx.last_mouse_y = screenHeight / 2;
    mlx.mouse_locked = 0;
    
    // Add these initializations:
    mlx.needs_render = 1;        // Start with needing a render
    mlx.last_render_time = 0;    // Initialize render timing
    
    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, screenWidth, screenHeight, "Cub3D Raycasting");
    mlx.img = mlx_new_image(mlx.mlx, screenWidth, screenHeight);
    mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
    
    // Set up hooks
    mlx_hook(mlx.win, 2, 1L << 0, handle_keys, &mlx);           // Key press
    mlx_hook(mlx.win, 3, 1L << 1, handle_key_release, &mlx);   // Key release
    mlx_hook(mlx.win, 4, 1L << 2, handle_mouse_press, &mlx);   // Mouse button press
    mlx_hook(mlx.win, 6, 1L << 6, handle_mouse_move, &mlx);    // Mouse movement
    mlx_loop_hook(mlx.mlx, render_loop, &mlx);                 // SEPARATE RENDER LOOP
    mlx_hook(mlx.win, 17, 0, close_hook, &mlx);               // Close button
    
    render_scene(&mlx);  // Initial render
    mlx_loop(mlx.mlx);
    
    return 0;
}

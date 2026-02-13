/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:00:55 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/02/10 19:21:53 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"
#include "../minilibx-linux/mlx.h"

#ifndef CUB3D_H
#define CUB3D_H

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

typedef struct s_sprite
{
	double x;
	double y;
	int texture_index;
	double distance;
} t_sprite;

typedef struct s_sprite_system
{
	t_sprite *sprites;     // Array of sprites
	int sprite_count;      // Number of sprites
	void *grass_img[2];    // Multiple grass textures (0 = grass1, 1 = grass2)
	char *grass_data[2];   // Multiple grass texture data
	int grass_width;       // Grass texture dimensions
	int grass_height;
} t_sprite_system;

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
	double *zbuffer;
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
	int texX;
    double step;
    double texPos;
	int hit_type;
} t_render;


typedef struct s_map
{
	char **rows;
	int	width;
	int	height;
	int	player_x;
	int	player_y;
	char	player_dir;
} t_map;

typedef struct s_color {
    int     floor_color;
    int     ceiling_color;
    int     floor_set;
    int     ceiling_set;
} t_color;

typedef struct s_textures
{
    // Keep existing fields for parsing compatibility
    char *north;
    char *south; 
    char *west;
    char *east;
    char *door;
    
    // Add optimized arrays for fast rendering
    void *img[5];        // [0]=north, [1]=south, [2]=west, [3]=east, [4]=door
    char *data[5];       // Texture data pointers [4] = door data
    
    // Texture dimensions
    int tex_width;
    int tex_height;
    int tex_width_shift;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_textures;

typedef struct s_door
{
    int x;
    int y;
    int is_open;
    float open_progress; // 0.0 = closed, 1.0 = fully open
} t_door;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_textures	textures;
	t_color		colors;
	t_map		maps;
	t_mlx       mlx;
	t_door *doors;
    int door_count;
	t_sprite_system sprites;
}	t_game;


/* Validation */
int validate_extension(const char *file);
int	validate_texture_file(const char *path);
int  validate_map_basic(t_map *map);
int	validate_map_basic(t_map *map);
int validate_map_closed(t_map *map);
/* Parsing */
int	parse_texture_line(char *line, t_game *game);
int	parse_textures(int fd, t_game *game);
int parse_rgb(char *rgb_str, t_color *data);
int parse_floor_color(char *line, t_color *data);
int parse_ceiling_color(char *line, t_color *data);
int parse_file(const char *path, t_game *game);
int	parse_map_line(char *line, t_map *map);
int	finalize_map(t_map *map);

/* Utils */
char	*trim_whitespace(char *str);
void trim_line(char *s);
int		is_blank(const char *s);
int is_allow_chars(char c);
int sanitize_row(const char *row);
int push_row(t_map *map, char *row_dup);


/* Free */
void cleanup_game(t_game *game);
void	free_textures(t_game *game);
void	free_map(t_map *map);
void free_mlx(t_game *game);

/* mlx */
int     init_mlx(t_game *game);
int     close_window(t_game *game);
int     key_press(int keycode, t_game *game);
#endif 


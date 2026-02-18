/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:00:55 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/02/18 17:25:27 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"
#include "../minilibx-linux/mlx.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sys/time.h"

#ifndef CUB3D_H
#define CUB3D_H

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
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
#define M_PI 3.1415926535897932384626433

typedef struct s_sprite
{
	double x;
	double y;
	int texture_index;
	double distance;
} t_sprite;

typedef struct s_sprite_system
{
	t_sprite *sprites;
	int sprite_count;
	double invDet;
	double spriteX;
	double spriteY;
	double transformX;
	double transformY;
	int texX;
	int texY;
	int color;
	int spriteScreenX;
	int spriteHeight;
	int spriteWidth;
	int horizonY;
	int groundY;
	int drawStartY;
	int drawStartX;
	int drawEndY;
	int drawEndX;
	void *grass_img[2];
	char *grass_data[2];
	int grass_width;
	int grass_height;
	int max_sprites;
	int grass_type;
	int grass_per_tile;
} t_sprite_system;

typedef struct s_minimap {
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
    int scan_y;
    int width_at_y;
    int current_x;
    int current_y_adj;
    int arrow_dx;
    int arrow_dy;
    int angle;
    double radian;
    int border_x;
    int border_y;
    int inner_border_x;
    int inner_border_y;
	double rand_x;
	double rand_y;
	int dot_size;
	int outline_size;
	int y;
	int x;
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

typedef struct s_mouse {
	int center_x ;
	int center_y;
	int delta_x;
	int delta_y ;
	double rotation;
	double oldDirX;
	double oldPlaneX;
}	t_mouse;

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

/* Minimap */
void init_minimap(t_minimap *minimap, t_mlx *mlx);
void draw_arrow_outline(t_mlx *mlx, t_minimap *minimap);
void draw_arrow_body(t_mlx *mlx, t_minimap *minimap);
void calculate_arrow_points(t_minimap *minimap);

/* Raycasting */
void initialize_dda_step_x(t_mlx *mlx, t_render *r);
void initialize_dda_step_y(t_mlx *mlx, t_render *r);
void perform_dda_step(t_render *r);

/* Rendering */
void render_scene(t_game *game);
int render_loop(t_game *game);
void initialize_mlx(t_mlx *mlx);
int render_loop_wrapper(void *param);
void render_start(t_mlx *mlx, t_render *r);
void draw_ceiling_floor(t_mlx *mlx, t_color *colors, int x, int draw_start, int draw_end);

/* Sprites */
void calculate_sprite_transform(t_mlx *mlx, t_sprite *sprite, t_sprite_system *sprites);
void calculate_sprite_screen_coords(t_mlx *mlx, t_sprite_system *sprites);
void calculate_sprite_draw_bounds(t_sprite_system *sprites);
void render_sprite_column(t_mlx *mlx, t_sprite_system *sprites, char *grass_data, int stripe);
void render_single_sprite(t_mlx *mlx, t_sprite *sprite, t_sprite_system *sprites);
int get_texture_pixel(char *texture_data, int tex_x, int tex_y, t_textures *tex);
int get_sprite_pixel(char *sprite_data, int tex_x, int tex_y, t_sprite_system *sprites);
void grass_loop_generating(t_game *game, t_minimap *minimap, t_sprite_system *sprites, int i);
void generate_grass_sprites(t_game *game, t_minimap *minimap);
int load_grass_texture(t_game *game);
void calculate_sprite_distances(t_mlx *mlx, t_sprite_system *sprites, int *rendered_count);
void swap_sprites(t_sprite *sprite1, t_sprite *sprite2);
void sort_sprites_by_distance(t_sprite_system *sprites);
void render_visible_sprites(t_mlx *mlx, t_sprite_system *sprites);
void render_sprites(t_mlx *mlx, t_sprite_system *sprites);

/* Controls */
void mouse_rotation(t_mouse *mouse, t_mlx *mlx);
int handle_mouse_move(int x, int y, t_mlx *mlx);
int handle_mouse_press(int button, int x, int y, t_mlx *mlx);
int handle_keys(int keycode, t_game *game);
int handle_key_release(int keycode, t_game *game);
int handle_vertical_movement(t_mlx *mlx, t_map *map, t_game *game);
int handle_horizontal_movement(t_mlx *mlx, t_map *map, t_game *game);

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


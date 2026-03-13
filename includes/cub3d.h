/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:38:17 by simgarci          #+#    #+#             */
/*   Updated: 2026/03/13 15:50:43 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include "libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "sys/time.h"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define MAX_SPRITES 1000
# define MOVEMENT_FPS 60
# define RENDER_FPS 60
# define TARGET_FPS 60
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define MOVE_SPEED 0.03
# define ROT_SPEED 0.015
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP_ARROW 65364
# define KEY_DOWN_ARROW 65362
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define MOUSE_SENS_X 0.001
# define MOUSE_SENS_Y 1.0  
# define MINIMAP_SIZE 200
# define MINIMAP_SCALE 8
# define MINIMAP_OFFSET 20
# define KEY_SHIFT 65505
# define KEY_INTERACT 101

typedef struct s_spr
{
	double	x;
	double	y;
	int		texture_index;
	double	distance;
}	t_spr;

typedef struct s_spr_system
{
	t_spr	*sprs;
	int		spr_count;
	double	inv_det;
	double	spr_x;
	double	spr_y;
	double	transform_x;
	double	transform_y;
	int		tex_x;
	int		tex_y;
	int		color;
	int		spr_screen_x;
	int		spr_height;
	int		spr_width;
	int		horizon_y;
	int		ground_y;
	int		draw_s_y;
	int		draw_s_x;
	int		draw_e_y;
	int		draw_e_x;
	void	*grass_img[2];
	char	*grass_data[2];
	int		grass_width;
	int		grass_height;
	int		max_sprs;
	int		grass_type;
	int		grass_per_tile;
}	t_spr_system;

typedef struct s_minimap
{
	int		map_start_x;
	int		map_start_y;
	int		center_x;
	int		center_y;
	int		radius;
	int		player_pixel_x;
	int		player_pixel_y;
	double	player_angle;
	int		arrow_length;
	int		arrow_width;
	double	rel_x;
	double	rel_y;
	double	rotated_x;
	double	rotated_y;
	double	world_x;
	double	world_y;
	int		map_x;
	int		map_y;
	int		color;
	int		pixel_x;
	int		pixel_y;
	int		dx;
	int		dy;
	int		distance_squared;
	int		spr_screen_x;
	int		screen_y;
	int		tip_x;
	int		tip_y;
	int		base_center_x;
	int		base_center_y;
	int		base_left_x;
	int		base_left_y;
	int		base_right_x;
	int		base_right_y;
	int		lx1;
	int		ly1;
	int		lx2;
	int		ly2;
	int		lx3;
	int		ly3;
	int		outline_dx;
	int		outline_dy;
	int		outline_dx1;
	int		outline_dy1;
	int		outline_dx2;
	int		outline_dy2;
	int		scan_y;
	int		width_at_y;
	int		current_x;
	int		current_y_adj;
	int		arrow_dx;
	int		arrow_dy;
	int		angle;
	double	radian;
	int		border_x;
	int		border_y;
	int		inner_border_x;
	int		inner_border_y;
	double	rand_x;
	double	rand_y;
	int		dot_size;
	int		outline_size;
	int		y;
	int		x;
}	t_minimap;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		key_state[10];
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	pitch;
	double	*zbuffer;
	int		last_mouse_x;
	int		last_mouse_y;
	int		mouse_locked;
	int		needs_render;
	long	last_render_time;
}	t_mlx;

typedef struct s_render
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dits_y;
	double	delta_dits_x;
	double	perp_wall_dist;
	int		draw_start;
	int		draw_end;
	int		horizon;
	int		line_height;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		x;
	int		y;
	int		tex_x;
	int		hit_type;
	double	step;
	double	tex_pos;
}	t_render;

typedef struct s_mouse
{
	int		center_x;
	int		center_y;
	int		delta_x;
	int		delta_y;
	double	rotation;
	double	olddir_x;
	double	oldplane_x;
}	t_mouse;

typedef struct s_map
{
	char	**rows;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_color
{
	int		floor_color;
	int		ceiling_color;
	int		floor_set;
	int		ceiling_set;
}	t_color;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*door;
	void	*img[5];
	char	*data[5];
	int		tex_width;
	int		tex_height;
	int		tex_width_shift;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_textures;

typedef struct s_door
{
	int		x;
	int		y;
	int		is_open;
	float	open_progress;
}	t_door;

typedef struct s_game
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_textures		txt;
	t_color			colors;
	t_map			maps;
	t_mlx			mlx;
	t_door			*doors;
	int				door_count;
	int				x;
	int				y;
	t_spr_system	spr;
}	t_game;

/* Validation */
int		validate_extension(const char *file);
int		validate_texture_file(const char *path);
int		validate_map_basic(t_map *map);
int		validate_map_basic(t_map *map);
int		validate_map_closed(t_map *map);

/* Parsing */
int		parse_texture_line(char *line, t_game *game);
int		parse_textures(int fd, t_game *game);
int		parse_rgb(char *rgb_str, t_color *data);
int		parse_floor_color(char *line, t_color *data);
int		parse_ceiling_color(char *line, t_color *data);
int		parse_file(const char *path, t_game *game);
int		parse_map_line(char *line, t_map *map);
int		finalize_map(t_map *map);
int		parse_map(int fd, t_game *game);

/* Minimap */
void	init_minimap(t_minimap *minimap, t_mlx *mlx);
void	draw_arrow_outline(t_mlx *mlx, t_minimap *minimap);
void	draw_arrow_body(t_mlx *mlx, t_minimap *minimap);
void	calculate_arrow_points(t_minimap *minimap);
void	draw_arrow_body(t_mlx *mlx, t_minimap *minimap);
void	draw_minimap(t_mlx *mlx, t_map *map, t_game *game);

/* Raycasting */
void	initialize_dda_step_x(t_mlx *mlx, t_render *r);
void	initialize_dda_step_y(t_mlx *mlx, t_render *r);
void	perform_dda_step(t_render *r);
void	data_update(t_mlx *mlx, t_render *r, t_game *game);
void	vertical_update(t_mlx *mlx, t_render *r, t_game *game);
void	process_continuous_input(t_game *game);

/* Rendering */
int		render_loop(t_game *game);
int		render_loop_wrapper(void *param);
void	render_scene(t_game *game);
void	initialize_mlx(t_mlx *mlx);
void	render_start(t_mlx *mlx, t_render *r);
void	draw_ceiling_floor(t_mlx *mlx, t_color *colors, t_render *r);
void	apply_dda(t_mlx *mlx, t_render *r, t_map *map, t_game *game);

/* Textures */
int		load_all_textures(t_game *game);
char	*get_wall_texture_fast(t_render *r, t_textures *textures);

/* sprs */
int		get_spr_pixel(char *spr_data, int tex_x,
			int tex_y, t_spr_system *sprs);
int		get_texture_pixel(char *texture_data, int tex_x,
			int tex_y, t_textures *tex);
int		load_grass_texture(t_game *game);
void	calculate_spr_transform(t_mlx *mlx, t_spr_system *sprs);
void	calculate_spr_screen_coords(t_mlx *mlx, t_spr_system *sprs);
void	calculate_spr_draw_bounds(t_spr_system *sprs);
void	render_sprite_column(t_mlx *mlx, t_spr_system *sprs,
			char *grass_data, int stripe);
void	render_single_spr(t_mlx *mlx, t_spr *spr,
			t_spr_system *sprs);
void	grass_loop_generating(t_game *game, t_minimap *minimap,
			t_spr_system *sprs);
void	generate_grass_sprite(t_game *game, t_minimap *minimap);
void	calculate_spr_distances(t_mlx *mlx, t_spr_system *sprs,
			int *rendered_count);
void	swap_sprs(t_spr *spr1, t_spr *spr2);
void	sort_sprs_by_distance(t_spr_system *sprs);
void	render_visible_sprs(t_mlx *mlx, t_spr_system *sprs);
void	render_sprite(t_mlx *mlx, t_spr_system *sprs);

/* Controls */
void	mouse_rotation(t_mouse *mouse, t_mlx *mlx);
int		handle_mouse_move(int x, int y, t_mlx *mlx);
int		handle_mouse_press(int button, int x, int y, t_mlx *mlx);
int		handle_keys(int keycode, t_game *game);
int		handle_key_release(int keycode, t_game *game);
int		handle_vertical_movement(t_mlx *mlx, t_map *map, t_game *game);
int		handle_horizontal_movement(t_mlx *mlx, t_map *map, t_game *game);
int		close_hook(t_mlx *mlx);
int		key_hook(int keycode, t_mlx *mlx);
void	calculate_texture_coords(t_mlx *mlx, t_render *r, t_game *game);
void	calculate_wall_distance(t_mlx *mlx, t_render *r);
void	rotate_left(t_mlx *mlx);
void	rotate_right(t_mlx *mlx);

/*Player*/
void	set_player_direction(t_mlx *mlx, char player_dir, double plane_length);
void	check_wall_hit(t_render *r, t_map *map, t_game *game);
void	interact_with_door(t_game *game);
void	initialize_player_from_map(t_mlx *mlx, t_map *map);
t_door	*find_door(t_game *game, int x, int y);

/* Utils */
long	get_time_ms(void);
char	*trim_whitespace(char *str);
void	trim_line(char *s);
void	draw_crosshair(t_mlx *mlx);
void	clear_image(t_mlx *data);
void	ft_mlx_pixel_put(t_mlx *data, int x, int y, int color);
int		validator(t_game *game);
int		is_blank(const char *s);
int		is_allow_chars(char c);
int		sanitize_row(const char *row);
int		push_row(t_map *map, char *row_dup);
int		get_map_value(t_map *map, int x, int y, t_game *game);
int		error_checker(t_game *game, int argc, char **argv);
int		apply_vignette(int color, int x, int y);
int		parse_error_checker(int ret, t_game *game);

/* Free */
void	cleanup_game(t_game *game);
void	free_textures(t_game *game);
void	free_map(t_map *map);
void	free_mlx(t_game *game);

/* mlx */
int		init_mlx(t_game *game);
int		close_window(t_game *game);
int		key_press(int keycode, t_game *game);

#endif
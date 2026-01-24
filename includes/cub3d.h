/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:00:55 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/01/24 20:53:31 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

#ifndef CUB3D_H
#define CUB3D_H

typedef struct s_map
{
	char **rows;
	int	width;
	int	height;
	int	player_x;
	int	player_y;
	char	player_dir;
} t_map;

typedef struct s_color
{
    int     floor_color;
    int     ceiling_color;
    int     floor_set;
    int     ceiling_set;
} t_color;

typedef struct s_textures
{
	char *north;
	char *south;
	char *west;
	char *east;
}	t_textures;

typedef struct s_game
{
	t_textures textures;
	t_color colors;
	t_map	maps;
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

#endif 
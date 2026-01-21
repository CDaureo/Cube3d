/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:00:55 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/01/21 13:09:52 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

#ifndef CUB3D_H
#define CUB3D_H

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
}	t_game;


/* Validation */
int validate_extension(const char *file);
/* Parsing */
int	validate_texture_file(const char *path);
int	parse_texture_line(char *line, t_game *game);
int	parse_textures(int fd, t_game *game);

/* Utils */
char	*trim_whitespace(char *str);
void	free_textures(t_game *game);
#endif 
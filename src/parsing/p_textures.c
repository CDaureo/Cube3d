/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_textures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:29:50 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/23 17:29:54 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	trim_textures(char *trim, t_game *game, char *path)
{
	if (ft_strncmp(trim, "NO ", 3) == 0)
	{
		path = trim_whitespace(trim + 3);
		game->textures.north = ft_strdup(path);
	}
	else if (ft_strncmp(trim, "SO ", 3) == 0)
	{
		path = trim_whitespace(trim + 3);
		game->textures.south = ft_strdup(path);
	}
	else if (ft_strncmp(trim, "WE ", 3) == 0)
	{
		path = trim_whitespace(trim + 3);
		game->textures.west = ft_strdup(path);
	}
	else if (ft_strncmp(trim, "EA ", 3) == 0)
	{
		path = trim_whitespace(trim + 3);
		game->textures.east = ft_strdup(path);
	}
	else if (ft_strncmp(trim, "DO ", 3) == 0)
	{
		path = trim_whitespace(trim + 3);
		game->textures.door = ft_strdup(path);
	}
}

int	parse_texture_line(char *line, t_game *game)
{
	char	*trim;
	char	*path;

	path = "NULL";
	trim = trim_whitespace(line);
	trim_textures(trim, game, path);
	return (1);
}

int	parse_textures(int fd, t_game *game)
{
	char	*line;
	int		counter;

	counter = 0;
	line = get_next_line(fd);
	while (counter < 5 && line)
	{
		if (ft_strncmp(line, "NO ", 3) == 0
			|| ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0
			|| ft_strncmp(line, "EA ", 3) == 0
			|| ft_strncmp(line, "DO ", 3) == 0)
		{
			parse_texture_line(line, game);
			counter++;
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	validator(game);
	return (1);
}

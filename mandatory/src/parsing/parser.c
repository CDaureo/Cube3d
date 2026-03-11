/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:30:11 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/25 11:55:03 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_map_line_start(const char *s)
{
	size_t	i;
	int		has_map_char;
	char	c;

	i = 0;
	has_map_char = 0;
	if (!s)
		return (0);
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i] && s[i] != '\n')
	{
		c = s[i];
		if (c == '0' || c == '1' || c == 'N' || c == 'S' || \
			c == 'E' || c == 'W' || c == 'D')
			has_map_char = 1;
		if (c != '0' && c != '1' && c != 'N' && c != 'S' && \
			c != 'E' && c != 'W' && c != 'D' && c != ' ' && c != '\t')
			return (0);
		i++;
	}
	return (has_map_char);
}

void	loop_doors(t_game *game, int door_index)
{
	while (game->y < game->maps.height)
	{
		game->x = 0;
		while (game->x < game->maps.width)
		{
			if (game->maps.rows[game->y][game->x] == 'D')
			{
				game->doors[door_index].x = game->x;
				game->doors[door_index].y = game->y;
				game->doors[door_index].is_open = 0;
				game->doors[door_index].open_progress = 0.0f;
				door_index++;
			}
			game->x++;
		}
		game->y++;
	}
}

void	parse_map_doors(t_game *game)
{
	int	door_count;
	int	door_index;

	game->y = 0;
	door_count = 0;
	while (game->y < game->maps.height)
	{
		game->x = 0;
		while (game->x < game->maps.width)
		{
			if (game->maps.rows[game->y][game->x] == 'D')
				door_count++;
			game->x++;
		}
		game->y++;
	}
	game->doors = malloc(sizeof(t_door) * door_count);
	game->door_count = door_count;
	door_index = 0;
	game->y = 0;
	loop_doors(game, door_index);
}

static int	parse_line(char *line, t_game *game)
{
	trim_line(line);
	if (is_blank(line))
		return (1);
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || \
		!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3) || \
		!ft_strncmp(line, "DO ", 3))
		return (parse_texture_line(line, game));
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_floor_color(line, &game->colors));
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_ceiling_color(line, &game->colors));
	if (is_map_line_start(line))
		return (parse_map_line(line, &game->maps));
	printf("Error:\nLine not recognised: %s\n", line);
	return (0);
}

int	parse_file(const char *path, t_game *game)
{
	int		fd;
	char	*line;
	int		ret;
	int		r;

	ret = 1;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (printf("Error:\nCannot be opened %s\n", path), 0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		r = parse_line(line, game);
		free(line);
		if (r == 0)
		{
			ret = 0;
			break ;
		}
		line = get_next_line(fd);
	}
	close(fd);
	if (!parse_error_checker(ret, game))
		return (0);
	return (parse_map_doors(game), 1);
}

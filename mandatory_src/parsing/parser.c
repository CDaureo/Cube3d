/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parser.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cdaureo- <cdaureo-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/02/23 17:30:11 by simgarci		  #+#	#+#			 */
/*   Updated: 2026/03/13 17:28:08 by cdaureo-		 ###   ########.fr	   */
/*																			*/
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
		if (c == '0' || c == '1' || c == 'N' || c == 'S'
			|| c == 'E' || c == 'W' || c == 'D')
			has_map_char = 1;
		if (c != '0' && c != '1' && c != 'N' && c != 'S'
			&& c != 'E' && c != 'W' && c != 'D' && c != ' ' && c != '\t')
			return (0);
		i++;
	}
	return (has_map_char);
}

static int	is_config_line(const char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "DO ", 3))
		return (1);
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		return (1);
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		return (1);
	return (0);
}

static int	parse_config_line(char *line, t_game *game)
{
	if (!is_config_line(line))
		return (printf("Error:\nLine not recognised: %s\n", line), 0);
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "DO ", 3))
		return (parse_texture_line(line, game));
	if (line[0] == 'F')
		return (parse_floor_color(line, &game->colors));
	return (parse_ceiling_color(line, &game->colors));
}

static int	parse_line(char *line, t_game *game, t_parse_state *st)
{
	trim_line(line);
	if (is_blank(line))
	{
		if (st->map_started)
			st->map_ended = 1;
		return (1);
	}
	if (is_map_line_start(line))
	{
		if (st->map_ended)
			return (printf("Error:\nMapa inválido: hueco en mapa\n"), 0);
		st->map_started = 1;
		return (parse_map_line(line, &game->maps));
	}
	if (st->map_started)
		return (printf("Error:\nLínea inválida del mapa: %s\n", line), 0);
	return (parse_config_line(line, game));
}

int	parse_file(const char *path, t_game *game)
{
	int				fd;
	int				ret;
	char			*line;
	t_parse_state	st;

	ret = 1;
	st.map_started = 0;
	st.map_ended = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (printf("Error:\nCannot be opened %s\n", path), 0);
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(line, game, &st))
			ret = 0;
		free(line);
		if (!ret)
			break ;
		line = get_next_line(fd);
	}
	close(fd);
	if (!parse_error_checker(ret, game))
		return (0);
	return (parse_map_doors(game), 1);
}

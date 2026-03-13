/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   p_textures.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cdaureo- <cdaureo-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/03/13 17:19:10 by cdaureo-		  #+#	#+#			 */
/*   Updated: 2026/03/13 17:33:38 by cdaureo-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	assign_texture_path(char *trim, t_game *game)
{
	char	*after;
	char	*path_token;
	char	**dst;
	size_t	i;

	dst = ptex_get_texture_dst(game, trim, &after);
	if (!dst)
		return (0);
	after = trim_whitespace(after);
	i = 0;
	while (after[i] && !is_space(after[i]))
		i++;
	if (i == 0)
		return (0);
	path_token = ptex_dup_n(after, i);
	if (!path_token)
		return (0);
	while (after[i] && is_space(after[i]))
		i++;
	if ((after[i] && after[i] != '\n') || !ptex_has_xpm_ext(path_token)
		|| access(path_token, R_OK) != 0)
		return (free(path_token), 0);
	if (*dst)
		free(*dst);
	return (*dst = path_token, 1);
}

void	trim_textures(char *trim, t_game *game)
{
	char	*after;
	char	*path_token;
	char	**dst;
	size_t	i;

	dst = ptex_get_texture_dst(game, trim, &after);
	if (!dst)
		return ;
	after = trim_whitespace(after);
	i = 0;
	while (after[i] && !is_space(after[i]))
		i++;
	if (i == 0)
		return ;
	path_token = ptex_dup_n(after, i);
	if (!path_token)
		return ;
	while (after[i] && is_space(after[i]))
		i++;
	if (after[i] != '\0' && after[i] != '\n')
		return (free(path_token));
	*dst = path_token;
}

int	parse_texture_line(char *line, t_game *game)
{
	char	*trim;

	trim = trim_whitespace(line);
	if (!assign_texture_path(trim, game))
		return (printf("Error:\nInvalid texture line: %s\n", line), 0);
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
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0
			|| ft_strncmp(line, "EA ", 3) == 0
			|| ft_strncmp(line, "DO ", 3) == 0)
		{
			if (parse_texture_line(line, game))
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

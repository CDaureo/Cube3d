/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_textures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:29:50 by simgarci          #+#    #+#             */
/*   Updated: 2026/03/13 15:35:08 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
        || c == '\v' || c == '\f');
}

static char	*dup_n(const char *s, size_t n)
{
    char	*ret;

    ret = malloc(n + 1);
    if (!ret)
        return (NULL);
    ft_memcpy(ret, s, n);
    ret[n] = '\0';
    return (ret);
}

void	trim_textures(char *trim, t_game *game)
{
    char	*after;
    char	*path_token;
    size_t	i;

    if (ft_strncmp(trim, "NO ", 3) == 0)
        after = trim + 3;
    else if (ft_strncmp(trim, "SO ", 3) == 0)
        after = trim + 3;
    else if (ft_strncmp(trim, "WE ", 3) == 0)
        after = trim + 3;
    else if (ft_strncmp(trim, "EA ", 3) == 0)
        after = trim + 3;
    else if (ft_strncmp(trim, "DO ", 3) == 0)
        after = trim + 3;
    else
        return ;
    after = trim_whitespace(after);
    i = 0;
    while (after[i] && !is_space(after[i]))
        i++;
    if (i == 0)
        return ; // no path token -> ignore to avoid crash
    path_token = dup_n(after, i);
    if (!path_token)
        return ;
    // ensure the rest contains only whitespace/newline
    while (after[i] && is_space(after[i]))
        i++;
    if (after[i] != '\0' && after[i] != '\n')
    {
        // invalid extra token after path, skip to avoid passing bad path
        free(path_token);
        return ;
    }
    if (ft_strncmp(trim, "NO ", 3) == 0)
        game->txt.north = path_token;
    else if (ft_strncmp(trim, "SO ", 3) == 0)
        game->txt.south = path_token;
    else if (ft_strncmp(trim, "WE ", 3) == 0)
        game->txt.west = path_token;
    else if (ft_strncmp(trim, "EA ", 3) == 0)
        game->txt.east = path_token;
    else if (ft_strncmp(trim, "DO ", 3) == 0)
        game->txt.door = path_token;
}

int	parse_texture_line(char *line, t_game *game)
{
    char	*trim;

    trim = trim_whitespace(line);
    trim_textures(trim, game);
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

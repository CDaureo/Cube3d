/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:50:42 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/01/22 13:14:07 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int is_map_line_start(const char *s)
{
    size_t i = 0;
    int    has_map_char = 0;

    if (!s) return 0;
    while (s[i] == ' ' || s[i] == '\t') i++;
    if (s[i] == '\0') return 0;
    while (s[i] && s[i] != '\n')
    {
        char c = s[i];
        if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
            has_map_char = 1;
        if (c != '0' && c != '1' && c != 'N' && c != 'S' &&
            c != 'E' && c != 'W' && c != ' ' && c != '\t')
            return 0;
        i++;
    }
    return has_map_char;
}

static int parse_line(char *line, t_game *game)
{
    // Ignorar líneas vacías o solo espacios
    if (is_blank(line))
        return 0;

    // Texturas (NO, SO, WE, EA)
    if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) ||
        !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
        return parse_texture_line(line, game);

    // Colores (F y C)
    if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
        return parse_floor_color(line, &game->colors);
    if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
        return parse_ceiling_color(line, &game->colors);
    if (is_map_line_start(line))
        return parse_map_line(line, &game->maps);
    
    
    // Línea desconocida
    printf("Error:\nLine not recognised: %s\n", line);
    return -1;
}

int parse_file(const char *path, t_game *game)
{
    int   fd;
    char *line;
    int   ret = 1;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (printf("Error:\nCannot be opened %s\n", path), 0);

    while ((line = get_next_line(fd)) != NULL)
    {
        if (parse_line(line, game) < 0)
            ret = 0;
        free(line);
        if (!ret)
            break;
    }
    close(fd);

    // Validaciones finales (texturas y colores definidos, etc.)
    if (ret && (!game->textures.north || !game->textures.south ||
                !game->textures.west || !game->textures.east))
        return (printf("Error:\nMissing textures\n"), 0);
    if (ret && (!game->colors.floor_set || !game->colors.ceiling_set))
        return (printf("Error:\nMissing colors F/C\n"), 0);

    return ret;
}


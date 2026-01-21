/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:50:42 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/01/21 13:53:43 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

    
    // Línea desconocida
    printf("Error:\nLínea no reconocida: %s\n", line);
    return -1;
}

int parse_file(const char *path, t_game *game)
{
    int   fd;
    char *line;
    int   ret = 1;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (printf("Error:\nNo se puede abrir %s\n", path), 0);

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
        return (printf("Error:\nFaltan texturas\n"), 0);
    if (ret && (!game->colors.floor_set || !game->colors.ceiling_set))
        return (printf("Error:\nFaltan colores F/C\n"), 0);

    return ret;
}


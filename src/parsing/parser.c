/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:36:49 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/02/10 19:40:46 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int is_map_line_start(const char *s)
{
    size_t i = 0;
    int has_map_char = 0;

    if (!s) 
        return 0;
    while (s[i] == ' ' || s[i] == '\t') 
        i++;
    if (s[i] == '\0') 
        return 0;
    while (s[i] && s[i] != '\n')
    {
        char c = s[i];
        if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D')  // Add 'D' here
            has_map_char = 1;
        if (c != '0' && c != '1' && c != 'N' && c != 'S' &&
            c != 'E' && c != 'W' && c != 'D' && c != ' ' && c != '\t')  // Add 'D' here
            return 0;
        i++;
    }
    return has_map_char;
}

void parse_map_doors(t_game *game)
{
    int door_count = 0;
    
    // First pass: count doors
    for (int y = 0; y < game->maps.height; y++)  // Changed from game->map_height
    {
        for (int x = 0; x < game->maps.width; x++)  // Changed from game->map_width
        {
            if (game->maps.rows[y][x] == 'D')  // Changed from game->map[y][x]
                door_count++;
        }
    }
    
    // Allocate door array
    game->doors = malloc(sizeof(t_door) * door_count);
    game->door_count = door_count;
    
    // Second pass: initialize doors
    int door_index = 0;
    for (int y = 0; y < game->maps.height; y++)  // Changed from game->map_height
    {
        for (int x = 0; x < game->maps.width; x++)  // Changed from game->map_width
        {
            if (game->maps.rows[y][x] == 'D')  // Changed from game->map[y][x]
            {
                game->doors[door_index].x = x;
                game->doors[door_index].y = y;
                game->doors[door_index].is_open = 0;
                game->doors[door_index].open_progress = 0.0f;
                door_index++;
            }
        }
    }
    
    printf("Found %d doors in the map\n", door_count);
}

static int parse_line(char *line, t_game *game)
{
    trim_line(line);

    // Ignorar líneas vacías o solo espacios
    if (is_blank(line))
        return (1);

    // Texturas (NO, SO, WE, EA, DO)
    if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) ||
        !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3) || 
        !ft_strncmp(line, "DO ", 3))
            return (parse_texture_line(line, game));

    // Colores (F y C)
    if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
        return parse_floor_color(line, &game->colors);
    if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
        return parse_ceiling_color(line, &game->colors);
    if (is_map_line_start(line))
        return parse_map_line(line, &game->maps);
        
        
    // Línea desconocida
    printf("Error:\nLine not recognised: %s\n", line);
    return (0);
}

int parse_file(const char *path, t_game *game)
{
    int   fd;
    char *line;
    int   ret;
    int   r;
    
    ret = 1;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (printf("Error:\nCannot be opened %s\n", path), 0);

    while ((line = get_next_line(fd)) != NULL)
    {
        r = parse_line(line, game);
        free(line);
        if (r == 0)
        {
            ret = 0;
            break;
        }
    }
    close(fd);

    if (!ret)
        return (printf("Error:\nInvalid .cub file (parse_line)\n"),0);
    if (game->maps.height == 0)
        return (printf("Error:\nNo map block found\n"), 0);
    if (!finalize_map(&game->maps))
        return (printf("Error:\nfinalize_map failed\n"), 0);
    if (!validate_map_basic(&game->maps))
        return (printf("Error:\nvalidate_map_basic failed\n"), 0);
    if (!validate_map_closed(&game->maps))
        return (printf("Error:\nMap is not closed by walls\n"), 0);
    if (!game->textures.north || !game->textures.south ||
        !game->textures.west || !game->textures.east || !game->textures.door)  // Add door check
        return (printf("Error:\nMissing textures\n"), 0);
    if (!game->colors.floor_set || !game->colors.ceiling_set)
        return (printf("Error:\nMissing colors F/C\n"), 0);
    parse_map_doors(game);
    
    return (1);
}

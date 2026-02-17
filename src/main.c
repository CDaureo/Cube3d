/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:07:55 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/02/17 16:10:22 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <string.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
    t_game	game;

    if (argc != 2)
        return (printf("Error\nUsage: %s <maps/map.cub>\n", argv[0]), 1);

    // Validar extensión del archivo
    if (!validate_extension(argv[1]))
        return (printf("Error\nExtension must be .cub\n"), 1);

    // Inicializar estructura a cero
    memset(&game, 0, sizeof(t_game));

    // Parsear archivo completo (texturas, colores y mapa)
    printf("DEBUG: Iniciando parsing...\n");
    if (!parse_file(argv[1], &game))
    {
        printf("DEBUG: parse_file falló\n");
        cleanup_game(&game);
        return 1;
    }

    printf("DEBUG: Parsing exitoso\n");

    // Debug: imprimir información parseada
    printf("✅ Parsing completado:\n");
    printf("  Texturas: N=%s S=%s W=%s E=%s\n",
           game.textures.north, game.textures.south,
           game.textures.west, game.textures.east);
    printf("  Colores: Floor=0x%06X Ceiling=0x%06X\n",
           game.colors.floor_color, game.colors.ceiling_color);
    printf("  Mapa: %dx%d\n", game.maps.width, game.maps.height);
    printf("  Jugador: (%d,%d) orientación=%c\n",
           game.maps.player_x, game.maps.player_y, game.maps.player_dir);

    // Aquí continuará la inicialización de MLX
    if (!init_mlx(&game))        
        return (cleanup_game(&game), 1);
    mlx_loop(game.mlx_ptr);

    cleanup_game(&game);
    return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:07:55 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/01/22 13:09:49 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <string.h> // memset

int	main(int argc, char **argv)
{
    t_game	game;

    if (argc != 2)
        return (printf("Error\nUso: %s <mapa.cub>\n", argv[0]), 1);

    memset(&game, 0, sizeof(t_game));

    if (!parse_file(argv[1], &game))
        return (cleanup_game(&game),1);

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

    // Aquí seguirías con la inicialización de MLX y el loop
    // init_mlx(&game);
    // game_loop(&game);

    // cleanup_game(&game);
    return 0;
}
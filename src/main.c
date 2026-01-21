/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:07:55 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/01/21 13:56:00 by cdaureo-         ###   ########.fr       */
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
        return 1;

    // Aquí seguirías con la inicialización de MLX y el loop
    // init_mlx(&game);
    // game_loop(&game);

    // cleanup_game(&game);
    return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:00:00 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/01/24 21:03:54 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * Hook para cerrar la ventana con la X roja
 */
int close_window(t_game *game)
{
    cleanup_game(game);
    exit(0);
    return (0);
}

/**
 * Hook para manejar eventos de teclado
 */
int key_press(int keycode, t_game *game)
{
    if (keycode == 65307) // ESC
    {
        close_window(game);
    }
    return (0);
}

/**
 * Inicializa miniLibX y crea la ventana
 */
int init_mlx(t_game *game)
{
    game->mlx_ptr = mlx_init();
    if (!game->mlx_ptr)
        return (printf("Error:\nFailed to initialize miniLibX\n"), 0);

    game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
    if (!game->win_ptr)
        return (printf("Error:\nFailed to create window\n"), 0);

    // Configurar hooks
    mlx_hook(game->win_ptr, 17, 0, close_window, game); // X roja
    mlx_key_hook(game->win_ptr, key_press, game);       // Teclas

    printf("✅ miniLibX initialized: %dx%d window\n", WIN_WIDTH, WIN_HEIGHT);
    return (1);
}


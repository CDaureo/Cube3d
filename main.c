/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:07:55 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/01/21 13:21:09 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
    t_game	game;
    int		fd;

    if (argc != 2)
    {
        ft_printf("Error\nUsage: ./cub3D <map.cub>\n");
        return (1);
    }
    
    ft_printf("🔍 Validating file: %s\n", argv[1]);
    
    if (!validate_extension(argv[1]))
    {
        ft_printf("Error\nInvalid file extension (must be .cub)\n");
        return (1);
    }
    
    ft_printf("✅ Extension validated\n");
    ft_printf("🔍 Opening file...\n");
    
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        ft_printf("Error\nCannot open file: %s\n", argv[1]);
        return (1);
    }
    
    ft_printf("✅ File opened (fd=%d)\n", fd);
    ft_memset(&game, 0, sizeof(t_game));
    
    ft_printf("🔍 Parsing textures...\n");
    
    if (!parse_textures(fd, &game))
    {
        ft_printf("❌ Texture parsing failed\n");
        free_textures(&game);
        close(fd);
        return (1);
    }
    
    ft_printf("\n✅ Textures loaded successfully!\n\n");
    ft_printf("=== Loaded Textures ===\n");
    ft_printf("  NO: %s\n", game.textures.north);
    ft_printf("  SO: %s\n", game.textures.south);
    ft_printf("  WE: %s\n", game.textures.west);
    ft_printf("  EA: %s\n", game.textures.east);
    
    free_textures(&game);
    close(fd);
    return (0);
}
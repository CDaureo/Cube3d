/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:07:55 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/01/19 14:11:14 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    if (argc != 2 || !validate_extension(argv[1]))
    {
        ft_printf("Error\n Usage: ./cub3D <map.cub>\n");
        return(1);
    }
return(0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_hooks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:53:54 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/19 13:54:04 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int key_hook(int keycode, t_mlx *mlx)
{
	(void)mlx;

	if(keycode == 65307)
		exit(0);
	return (0);
}

int close_hook(t_mlx *mlx)
{
	(void)mlx;

	exit(0);
}

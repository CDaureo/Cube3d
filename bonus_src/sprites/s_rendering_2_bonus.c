/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_rendering_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:08:56 by simgarci          #+#    #+#             */
/*   Updated: 2026/03/12 13:26:34 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_spr_distances(t_mlx *mlx, t_spr_system *spr, \
		int *rendered_count)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	*rendered_count = 0;
	while (i < spr->spr_count)
	{
		dx = spr->sprs[i].x - mlx->pos_x;
		dy = spr->sprs[i].y - mlx->pos_y;
		spr->sprs[i].distance = dx * dx + dy * dy;
		if (spr->sprs[i].distance > 27.0)
			spr->sprs[i].distance = -1;
		else
			(*rendered_count)++;
		i++;
	}
}

void	swap_spr(t_spr *spr1, t_spr *spr2)
{
	t_spr	temp;

	temp = *spr1;
	*spr1 = *spr2;
	*spr2 = temp;
}

void	sort_spr_by_distance(t_spr_system *spr)
{
	int	i;
	int	j;

	i = 0;
	while (i < spr->spr_count - 1)
	{
		j = 0;
		while (j < spr->spr_count - 1)
		{
			if (spr->sprs[j].distance >= 0 && \
					spr->sprs[j + 1].distance >= 0 && \
					spr->sprs[j].distance < spr->sprs[j + 1].distance)
			{
				swap_spr(&spr->sprs[j], &spr->sprs[j + 1]);
			}
			j++;
		}
		i++;
	}
}

void	render_visible_spr(t_mlx *mlx, t_spr_system *spr)
{
	int	i;

	i = 0;
	while (i < spr->spr_count)
	{
		if (spr->sprs[i].distance >= 0)
			render_single_spr(mlx, &spr->sprs[i], spr);
		i++;
	}
}

void	render_sprite(t_mlx *mlx, t_spr_system *spr)
{
	int	rendered_count;

	calculate_spr_distances(mlx, spr, &rendered_count);
	sort_spr_by_distance(spr);
	render_visible_spr(mlx, spr);
}

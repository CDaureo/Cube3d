/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_rendering_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:08:56 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/25 12:55:34 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_spr_distances(t_mlx *mlx, t_spr_system *sprs, \
		int *rendered_count)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	*rendered_count = 0;
	while (i < sprs->spr_count)
	{
		dx = sprs->sprs[i].x - mlx->posX;
		dy = sprs->sprs[i].y - mlx->posY;
		sprs->sprs[i].distance = dx * dx + dy * dy;
		if (sprs->sprs[i].distance > 64.0)
			sprs->sprs[i].distance = -1;
		else
			(*rendered_count)++;
		i++;
	}
}

void	swap_sprs(t_spr *spr1, t_spr *spr2)
{
	t_spr	temp;

	temp = *spr1;
	*spr1 = *spr2;
	*spr2 = temp;
}

void	sort_sprs_by_distance(t_spr_system *sprs)
{
	int	i;
	int	j;

	i = 0;
	while (i < sprs->spr_count - 1)
	{
		j = 0;
		while (j < sprs->spr_count - 1)
		{
			if (sprs->sprs[j].distance >= 0 && \
					sprs->sprs[j + 1].distance >= 0 && \
					sprs->sprs[j].distance < sprs->sprs[j + 1].distance)
			{
				swap_sprs(&sprs->sprs[j], &sprs->sprs[j + 1]);
			}
			j++;
		}
		i++;
	}
}

void	render_visible_sprs(t_mlx *mlx, t_spr_system *sprs)
{
	int	i;

	i = 0;
	while (i < sprs->spr_count)
	{
		if (sprs->sprs[i].distance >= 0)
			render_single_spr(mlx, &sprs->sprs[i], sprs);
		i++;
	}
}

void	render_sprs(t_mlx *mlx, t_spr_system *sprs)
{
	int	rendered_count;

	calculate_spr_distances(mlx, sprs, &rendered_count);
	sort_sprs_by_distance(sprs);
	render_visible_sprs(mlx, sprs);
}

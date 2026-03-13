/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_textures_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:40:23 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/03/13 17:41:31 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ptex_dup_n(const char *s, size_t n)
{
	char	*ret;

	ret = malloc(n + 1);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s, n);
	ret[n] = '\0';
	return (ret);
}

char	**ptex_get_texture_dst(t_game *game, char *trim, char **after)
{
	if (ft_strncmp(trim, "NO ", 3) == 0)
		return (*after = trim + 3, &game->txt.north);
	if (ft_strncmp(trim, "SO ", 3) == 0)
		return (*after = trim + 3, &game->txt.south);
	if (ft_strncmp(trim, "WE ", 3) == 0)
		return (*after = trim + 3, &game->txt.west);
	if (ft_strncmp(trim, "EA ", 3) == 0)
		return (*after = trim + 3, &game->txt.east);
	if (ft_strncmp(trim, "DO ", 3) == 0)
		return (*after = trim + 3, &game->txt.door);
	return (NULL);
}

int	ptex_has_xpm_ext(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".xpm", 4) == 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:14:57 by cdaureo-          #+#    #+#             */
/*   Updated: 2026/03/12 14:05:43 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*File Validator*/
int	validate_extension(const char *file)
{
	const char	*ext;

	if (!file)
		return (0);
	ext = ft_strrchr(file, '.');
	if (!ext)
	{
		printf("Error:\nInvalid file name (missing .cub): %s\n", file);
		return (0);
	}
	if (ft_strcmp(ext, ".cub") == 0)
		return (1);
	printf("Error:\nInvalid extension (require .cub): %s\n", file);
	return (0);
}

/* Valida que el archivo de textura exista y sea accesible */
int	validate_texture_file(const char *path)
{
	int	fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (printf("Error:\nTexture file not accesible; %s\n", path));
	close(fd);
	return (1);
}

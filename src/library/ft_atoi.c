/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:38:58 by simgarci          #+#    #+#             */
/*   Updated: 2026/02/13 15:47:06 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_atoi(const char *nptr)
{
	int	val;
	int	i;
	int	nminus;

	val = 0;
	i = 0;
	nminus = 1;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		++i;
	if (nptr[i]  == '"' || nptr[i] == '\'')
		++i;
	while (nptr[i] == ' ' || nptr[i] == '\t')
		++i;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			nminus = -1;
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9'))
	{
		val = val * 10 + (nptr[i] - '0');
		i++;
	}
	return (val * nminus);
}

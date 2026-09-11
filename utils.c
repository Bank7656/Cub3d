/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 18:36:51 by thacharo          #+#    #+#             */
/*   Updated: 2026/09/11 16:45:39 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(int c)
{
	if (c == ' ')
		return (1);
	else if (c == '\f')
		return (1);
	else if (c == '\n')
		return (1);
	else if (c == '\r')
		return (1);
	else if (c == '\t')
		return (1);
	else if (c == '\v')
		return (1);
	return (0);
}

char	**dup_map(char **src)
{
	int		i;
	char	**dst;

	i = 0;
	while (src[i])
		i++;
	dst = ft_calloc(i + 1, sizeof(char *));
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
			return (free_map(dst), NULL);
		i++;
	}
	return (dst);
}

void	free_map(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr);
		i++;
	}
	free(arr);
}

int	free_arr(char **arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 22:47:29 by thacharo          #+#    #+#             */
/*   Updated: 2026/09/08 22:49:35 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void clear_map(char **map);

void	clear_game(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g->scene.texture[i])
		{
			mlx_delete_texture(g->scene.texture[i]);
			g->scene.texture[i] = NULL;
		}
		i++;
	}
	if (g->map)
	{
		clear_map(g->map);
		g->map = NULL;
	}
	if (g->mlx)
		mlx_terminate(g->mlx);
}

static void clear_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

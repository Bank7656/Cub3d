/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 22:47:29 by thacharo          #+#    #+#             */
/*   Updated: 2026/09/13 15:15:31 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clear_textures(t_game *g);

void	clear_game(t_game *g)
{
	clear_textures(g);
	if (g->map)
	{
		clear_grid(g->map);
		g->map = NULL;
	}
	if (g->lines)
	{
		clear_grid(g->lines);
		g->lines = NULL;
	}
	if (g->mlx)
	{
		mlx_terminate(g->mlx);
		g->mlx = NULL;
	}
}

static void	clear_textures(t_game *g)
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
}

void clear_grid(char **map)
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

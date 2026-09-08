/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 13:34:54 by thacharo          #+#    #+#             */
/*   Updated: 2026/09/08 17:35:53 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int set_texture(t_game *g, char *path, int side)
{
	while (*path == ' ' || *path == '\t')
		path++;
	if (*path == '\0')
		return (0);
	if (g->scene.texture[side])
		return (0);
	g->scene.texture[side] = mlx_load_png(path);
	if (!g->scene.texture[side])
		return (0);
	return (1);
}

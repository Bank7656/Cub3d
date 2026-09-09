/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 13:34:54 by thacharo          #+#    #+#             */
/*   Updated: 2026/09/09 12:40:52 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_texture(t_game *g, char *path, int side)
{
	int i;

	while (ft_isspace(*path))
		path++;
	if (*path == '\0')
		error_exit(g, "Missing texture path");
	i = ft_strlen(path);
	while (ft_isspace(path[i - 1]))
		i--;
	path[i] = '\0';
	if (g->scene.texture[side])
		error_exit(g, "Texture side already exists");
	g->scene.texture[side] = mlx_load_png(path);
	if (!g->scene.texture[side])
		error_exit(g, mlx_strerror(mlx_errno));
	return ;
}

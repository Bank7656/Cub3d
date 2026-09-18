/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 14:18:09 by thacharo          #+#    #+#             */
/*   Updated: 2026/09/18 15:28:39 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_texture_colour(mlx_texture_t *t, int x, int y)
{
	size_t	pixel_pos;
	uint8_t	*p;

	pixel_pos = (y * t->width + x) * t->bytes_per_pixel;
	p = &t->pixels[pixel_pos];
	return ((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}

mlx_texture_t	*get_texture_side(t_game *g, t_ray *r)
{
	if (r->side == 1 && r->step_y > 0)
		return (g->scene.texture[NORTH]);
	else if (r->side == 1 && r->step_y < 0)
		return (g->scene.texture[SOUTH]);
	else if (r->side == 0 && r->step_x < 0)
		return (g->scene.texture[EAST]);
	else if (r->side == 0 && r->step_x > 0)
		return (g->scene.texture[WEST]);
	return (NULL);
}

int	get_texture_x(t_game *g, t_ray *r, mlx_texture_t *t)
{
	int		texture_x;
	double	wall_x;

	if (r->side == 0)
		wall_x = g->player.pos.y + r->perp_wall_dist * r->dir.y;
	else
		wall_x = g->player.pos.x + r->perp_wall_dist * r->dir.x;
	wall_x -= floor(wall_x);
	texture_x = (int)(wall_x * t->width);
	if (texture_x >= (int)t->width)
		texture_x = t->width - 1;
	if ((r->side == 0 && r->dir.x > 0) || (r->side == 1 && r->dir.y < 0))
		texture_x = t->width - texture_x - 1;
	return (texture_x);
}

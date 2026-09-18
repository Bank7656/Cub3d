/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 18:42:38 by thacharo          #+#    #+#             */
/*   Updated: 2026/09/18 15:22:26 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_wall_bounds(t_ray *r);

void	draw_background(t_game *g)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(g->img, x, y, g->scene.ceiling);
			else
				mlx_put_pixel(g->img, x, y, g->scene.floor);
			x++;
		}
		y++;
	}
}

void	draw_column(t_game *g, t_ray *r, int x)
{
	int				y;
	t_tex			tex;
	mlx_texture_t	*texture;

	set_wall_bounds(r);
	texture = get_texture_side(g, r);
	tex.x = get_texture_x(g, r, texture);
	tex.step = (double)texture->height / r->line_height;
	tex.pos = (r->draw_start - HEIGHT / 2.0 + r->line_height / 2.0) * tex.step;
	y = r->draw_start;
	while (y <= r->draw_end)
	{
		tex.y = (int)tex.pos;
		if (tex.y >= (int)texture->height)
			tex.y = texture->height - 1;
		tex.pos += tex.step;
		mlx_put_pixel(g->img, x, y, get_texture_colour(texture, tex.x, tex.y));
		y++;
	}
}

static void	set_wall_bounds(t_ray *r)
{
	if (r->side == 0)
		r->perp_wall_dist = r->side_dist.x - r->delta_dist.x;
	else
		r->perp_wall_dist = r->side_dist.y - r->delta_dist.y;
	if (r->perp_wall_dist < 0.0001)
		r->perp_wall_dist = 0.0001;
	r->line_height = (int)(HEIGHT / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + HEIGHT / 2;
	if (r->draw_end >= HEIGHT)
		r->draw_end = HEIGHT - 1;
}

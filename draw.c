/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 18:42:38 by thacharo          #+#    #+#             */
/*   Updated: 2026/08/29 18:43:08 by thacharo         ###   ########.fr       */
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
				mlx_put_pixel(g->img, x, y, g->ceiling);
			else
				mlx_put_pixel(g->img, x, y, g->floor);
			x++;
		}
		y++;
	}
}

void	draw_column(t_game *g, t_ray *r, int x)
{
	int			y;
	uint32_t	colour;

	set_wall_bounds(r);
	if (r->side == 0)
		colour = 0xAA3333FF;
	else
		colour = 0x772222FF;
	y = r->draw_start;
	while (y <= r->draw_end)
	{
		mlx_put_pixel(g->img, x, y, colour);
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

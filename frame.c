/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 18:25:56 by thacharo          #+#    #+#             */
/*   Updated: 2026/08/29 18:42:31 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_column(t_game *g, int x);
static void	run_dda(t_game *g, t_ray *r);

void	frame(void *param)
{
	int		x;
	t_game	*g;

	g = (t_game *)param;
	draw_background(g);
	handle_input(g);
	x = 0;
	while (x < WIDTH)
	{
		render_column(g, x);
		x++;
	}
}

static void	render_column(t_game *g, int x)
{
	t_ray	ray;

	init_ray(g, &ray, x);
	run_dda(g, &ray);
	draw_column(g, &ray, x);
}

static void	run_dda(t_game *g, t_ray *r)
{
	while (!r->hit)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta_dist.x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist.y += r->delta_dist.y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (g->map[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}

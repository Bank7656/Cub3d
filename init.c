/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 18:41:13 by thacharo          #+#    #+#             */
/*   Updated: 2026/08/29 18:42:00 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_player_direction(char c);
static void	set_orientation(t_player *p, char c);
static void	set_step_and_side(t_game *g, t_ray *r);

int	init_player(t_game *g)
{
	int	y;
	int	x;
	int	ret;

	y = 0;
	ret = 0;
	while (y < g->map_height)
	{
		x = 0;
		while (x < g->map_width && g->map[y][x])
		{
			if (is_player_direction(g->map[y][x]))
			{
				ret = 1;
				g->player.pos.x = x + 0.5;
				g->player.pos.y = y + 0.5;
				set_orientation(&g->player, g->map[y][x]);
				g->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	return (ret);
}

void	init_ray(t_game *g, t_ray *r, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	r->dir.x = g->player.dir.x + g->player.plane.x * camera_x;
	r->dir.y = g->player.dir.y + g->player.plane.y * camera_x;
	r->map_x = (int)g->player.pos.x;
	r->map_y = (int)g->player.pos.y;
	r->delta_dist.x = fabs(1 / r->dir.x);
	r->delta_dist.y = fabs(1 / r->dir.y);
	r->hit = 0;
	r->side = 0;
	set_step_and_side(g, r);
	return ;
}

static void	set_step_and_side(t_game *g, t_ray *r)
{
	if (r->dir.x < 0)
	{
		r->step_x = -1;
		r->side_dist.x = (g->player.pos.x - r->map_x) * r->delta_dist.x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist.x = (r->map_x + 1.0 - g->player.pos.x) * r->delta_dist.x;
	}
	if (r->dir.y < 0)
	{
		r->step_y = -1;
		r->side_dist.y = (g->player.pos.y - r->map_y) * r->delta_dist.y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist.y = (r->map_y + 1.0 - g->player.pos.y) * r->delta_dist.y;
	}
}

static int	is_player_direction(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		return (1);
	}
	return (0);
}

static void	set_orientation(t_player *p, char c)
{
	if (c == 'N')
	{
		p->dir.x = 0;
		p->dir.y = -1;
	}
	else if (c == 'S')
	{
		p->dir.x = 0;
		p->dir.y = 1;
	}
	else if (c == 'E')
	{
		p->dir.x = 1;
		p->dir.y = 0;
	}
	else if (c == 'W')
	{
		p->dir.x = -1;
		p->dir.y = 0;
	}
	p->plane.x = -1 * (p->dir.y * 0.66);
	p->plane.y = p->dir.x * 0.66;
}

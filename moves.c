/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 18:28:59 by thacharo          #+#    #+#             */
/*   Updated: 2026/08/29 18:39:14 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		try_move(t_game *g, double dx, double dy);
static double	margin(double d, double m);
static int		is_walkable(t_game *g, double x, double y);
static void		rotate(t_player *p, double angle);

void	handle_input(t_game *g)
{
	double	speed;
	double	rot;

	speed = 3 * g->mlx->delta_time;
	rot = 2 * g->mlx->delta_time;
	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
		try_move(g, g->player.dir.x * speed, g->player.dir.y * speed);
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
		try_move(g, -g->player.dir.x * speed, -g->player.dir.y * speed);
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
		try_move(g, -g->player.plane.x * speed, -g->player.plane.y * speed);
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
		try_move(g, g->player.plane.x * speed, g->player.plane.y * speed);
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
		rotate(&g->player, -rot);
	if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
		rotate(&g->player, rot);
}

static void	rotate(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir.x;
	old_plane_x = p->plane.x;
	p->dir.x = p->dir.x * cos(angle) - p->dir.y * sin(angle);
	p->dir.y = old_dir_x * sin(angle) + p->dir.y * cos(angle);
	p->plane.x = p->plane.x * cos(angle) - p->plane.y * sin(angle);
	p->plane.y = old_plane_x * sin(angle) + p->plane.y * cos(angle);
}

static void	try_move(t_game *g, double dx, double dy)
{
	t_vec	*pos;

	pos = &g->player.pos;
	if (is_walkable(g, pos->x + dx + margin(dx, 0.2), pos->y))
		pos->x += dx;
	if (is_walkable(g, pos->x, pos->y + dy + margin(dy, 0.2)))
		pos->y += dy;
}

static int	is_walkable(t_game *g, double x, double y)
{
	if (x < 0 || y < 0 || x >= g->map_width || y >= g->map_height)
		return (0);
	if (g->map[(int)y][(int)x] != '1')
		return (1);
	return (0);
}

static double	margin(double d, double m)
{
	if (d > 0)
		return (m);
	if (d < 0)
		return (-m);
	else
		return (0);
}

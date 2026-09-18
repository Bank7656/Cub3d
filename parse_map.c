/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:42:43 by thacharo          #+#    #+#             */
/*   Updated: 2026/09/18 15:50:08 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_checker(t_game *g)
{
	int	i;
	int	map_start;

	i = 0;
	while (g->lines[i] != NULL)
	{
		if (g->lines[i][0] == '\0')
		{
			i++;
			continue ;
		}
		if (is_all_values_parse(g))
			break ;
		parse_line(g, g->lines[i]);
		i++;
	}
	map_start = i;
	if (!check_no_blank_lines(g->lines, map_start))
		error_exit(g, "Map incomplete");
	if (!check_map_character(g->lines, map_start))
		error_exit(g, "Invalid character");
	if (!get_map_dimension(g, g->lines, map_start))
		error_exit(g, "Map Error");
	return (map_start);
}

void	check_map_border(t_game *g, int map_idx)
{
	flood_fill(g, (int)g->player.pos.x, (int)g->player.pos.y);
	clear_grid(g->map);
	g->map = NULL;
	load_map(g, g->lines, map_idx);
}

int	get_map_dimension(t_game *g, char **lines, int idx)
{
	int	len;

	g->map_width = 0;
	g->map_height = 0;
	while (lines[idx] != NULL)
	{
		len = ft_strlen(lines[idx]);
		if (len > g->map_width)
			g->map_width = len;
		g->map_height++;
		idx++;
	}
	if (g->map_width == 0)
		return (0);
	return (1);
}

void	load_map(t_game *g, char **lines, int idx)
{
	int		i;
	int		j;

	i = 0;
	g->map = (char **)ft_calloc(g->map_height + 1, sizeof(char *));
	if (!g->map)
		error_exit(g, "Cannot Malloc");
	while (lines[idx] != NULL)
	{
		j = 0;
		g->map[i] = (char *)ft_calloc(g->map_width + 1, sizeof(char));
		if (!g->map[i])
			error_exit(g, "Cannot Malloc");
		while (lines[idx][j] != '\0')
		{
			g->map[i][j] = lines[idx][j];
			j++;
		}
		ft_memset(g->map[i] + j, ' ', g->map_width - j);
		i++;
		idx++;
	}
	g->map[i] = NULL;
}

void	flood_fill(t_game *g, int x, int y)
{
	if (x < 0 || y < 0 || x >= g->map_width || y >= g->map_height)
		error_exit(g, "Map is not enclosed with the wall");
	if (g->map[y][x] == ' ')
		error_exit(g, "Map is not enclosed with the wall");
	if (g->map[y][x] == '1' || g->map[y][x] == 'v')
		return ;
	g->map[y][x] = 'v';
	flood_fill(g, x + 1, y);
	flood_fill(g, x - 1, y);
	flood_fill(g, x, y + 1);
	flood_fill(g, x, y - 1);
}

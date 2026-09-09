/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 13:31:48 by thacharo          #+#    #+#             */
/*   Updated: 2026/09/09 12:07:09 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	match_id(const char *line, const char *id); 

int	parse_line(t_game *g, char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (match_id(line, "NO"))
		set_texture(g, line + 2, NORTH);
	else if (match_id(line, "SO"))
		set_texture(g, line + 2, SOUTH);
	else if (match_id(line, "EA"))
		set_texture(g, line + 2, EAST);
	else if (match_id(line, "WE"))
		set_texture(g, line + 2, WEST);
	else if (match_id(line, "F"))
		set_colour(g, line + 1, &g->scene.floor);
	else if (match_id(line, "C"))
		set_colour(g, line + 1, &g->scene.ceiling);
	return (0);
}

static int	match_id(const char *line, const char *id)
{
	int	len;

	len = ft_strlen(id);
	if (ft_strncmp(line, id, len) != 0)
		return (0);
	if (!ft_isspace(line[len]))
		return (0);
	return (1);
}

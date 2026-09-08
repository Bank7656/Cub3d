/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 13:31:48 by thacharo          #+#    #+#             */
/*   Updated: 2026/09/08 22:47:08 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	match_id(const char *line, const char *id); 

int	parse_line(t_game *g, char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (match_id(line, "NO"))
		return (set_texture(g, line + 2, NORTH));
	if (match_id(line, "SO"))
		return (set_texture(g, line + 2, SOUTH));
	if (match_id(line, "EA"))
		return (set_texture(g, line + 2, EAST));
	if (match_id(line, "WE"))
		return (set_texture(g, line + 2, WEST));
	if (match_id(line, "F"))
		return (set_colour(g, line + 1, &g->scene.floor));
	if (match_id(line, "C"))
		return (set_colour(g, line + 1, &g->scene.ceiling));
	return (0);
}

static int	match_id(const char *line, const char *id)
{
	int	len;

	len = ft_strlen(id);
	if (ft_strncmp(line, id, len) != 0)
		return (0);
	if (line[len] != ' ' && line[len] != '\t')
		return (0);
	return (1);
}

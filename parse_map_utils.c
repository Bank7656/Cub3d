/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:44:51 by thacharo          #+#    #+#             */
/*   Updated: 2026/09/18 15:50:39 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_filename(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len <= 4 || ft_strncmp(name + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

/* packed colour always has 0xFF alpha, so 0 means unset */
int	is_all_values_parse(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g->scene.texture[i] == NULL)
			return (0);
		i++;
	}
	if (g->scene.floor == 0 || g->scene.ceiling == 0)
		return (0);
	return (1);
}

int	check_no_blank_lines(char **lines, int idx)
{
	while (lines[idx] != NULL)
	{
		if (lines[idx][0] == '\0')
			return (0);
		idx++;
	}
	return (1);
}

int	is_valid_map_character(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	check_map_character(char **lines, int idx)
{
	int	i;

	while (lines[idx] != NULL)
	{
		i = 0;
		while (lines[idx][i] != '\0')
		{
			if (!is_valid_map_character(lines[idx][i]))
				return (0);
			i++;
		}
		idx++;
	}
	return (1);
}

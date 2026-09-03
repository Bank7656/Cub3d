/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 23:46:07 by thacharo          #+#    #+#             */
/*   Updated: 2026/09/03 23:47:31 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_comma(char *line);
static int  parse_component(char **line, int *output);

int set_colour(t_game *game, char *line, uint32_t *scene)
{
	int	i;
	int	rgb[3];

	if (count_comma(line) != 2)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (!parse_component(&line, &rgb[i]))
			return (1);
		while (*line == ' ' || *line == '\t')
			line++;
		if (i < 2)
		{
			if (*line != ',')
				return (0);
			line++;
		}
		i++;
	}
	if (*line != '\0')
		return (0);
	*scene = (rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xFF;
	return (1);
}

static int	count_comma(char *line)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ',')
			count++; 
		i++;
	}
	return (count);
}

static int  parse_component(char **line, int *output)
{
	int	i;
	int	value;

	value = 0;
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (!ft_isdigit(**line))
		return (0);
	while (ft_isdigit(**line))
	{
		value = value * 10 + (**line - '0');
		if (value > 255)
			return (1);
		(*line)++;
	}
	*output = value;
	return (1);
}
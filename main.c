/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 18:39:21 by thacharo          #+#    #+#             */
/*   Updated: 2026/09/03 22:27:02 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char *g_map[] = {
	"111111",
	"100101",
	"101001",
	"101001",
	"101001",
	"101001",
	"100001",
	"1100N1",
	"111111",
	NULL
};

int		match_id(char *line, char *id)
{
	int	len;

	len = ft_strlen(id);
	if (ft_strncmp(line, id, len) != 0)
		return (0);
    if (line[len] != ' ' && line[len] != '\t')
        return (0);
    return (1);
}

int set_texture(t_game *g, char *line)
{
	(void)g;
	(void)line;
	return (1);
}

// int set_colour(t_game *game, char *line, uint32_t *scene)
// {
// 	(void)game;
// 	uint32_t	hex;
// 	char		**colour;
// 	int			rgb[3];

	

// 	colour = ft_split(line, ',');
// 	if (!colour)
// 		return (0);
// 	int	i = 0;
// 	while (colour[i] != NULL)
// 		i++;

		
// 	if (i != 3)
// 	{
// 		while (i >= 0)
// 		{
// 			free(colour[i]);
// 			i--;
// 		}
// 		free(colour);
// 		printf("Test\n");
// 		return (0);
// 	}

// 	rgb[0] = ft_atoi(colour[0]);
// 	rgb[1] = ft_atoi(colour[1]);
// 	rgb[2] = ft_atoi(colour[2]);
// 	*scene = (rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xFF;
// 	return (1);
// }
int	count_comma(char *line)
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

int	parse_component(char **line, int *output)
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

int	parse_line(t_game *g, char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (match_id(line, "NO"))
		return (set_texture(g, line + 2));
	if (match_id(line, "SO"))
		return (set_texture(g, line + 2));
	if (match_id(line, "EA"))
		return (set_texture(g, line + 2));
	if (match_id(line, "WE"))
		return (set_texture(g, line + 2));
	if (match_id(line, "F"))
		return (set_colour(g, line + 1, &g->floor));
	if (match_id(line, "C"))
		return (set_colour(g, line + 1, &g->ceiling));
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
		return (EXIT_FAILURE);

	// Init constant
	g.map = dup_map(g_map);
	g.map_width = 6;
	g.map_height = 9;
	g.ceiling = 0x87CEEBFF;
	g.floor = 0x5A4632FF;
	//

	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Error\n");
		return (EXIT_FAILURE);
	}
	char **lines = read_file(fd);
	if (!lines)
	{
		printf("Error\n");
		return (EXIT_FAILURE);
	}

	
	int i = 0;
	while (lines[i] != NULL)
	{
		if (lines[i][0] == '\0')
		{
			i++;
			continue;		
		}
		parse_line(&g, lines[i]);
		// if (!parse_line(&g, lines[i]))
		// {
		// 	printf("[%s]\n", lines[i]);
		// 	printf("Error\n");
		// 	// Need to free lines (**)
		// 	return (EXIT_FAILURE);
		// }
		printf("%s\n", lines[i]);
		i++;
	}


	if (!init_player(&g))
	{
		printf("Error\n");
		return (EXIT_FAILURE);
	}
	g.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!g.mlx)
		return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	g.img = mlx_new_image(g.mlx, WIDTH, HEIGHT);
	if (!g.img || mlx_image_to_window(g.mlx, g.img, 0, 0) == -1)
		return (mlx_close_window(g.mlx), EXIT_FAILURE);
	mlx_loop_hook(g.mlx, frame, &g);
	mlx_key_hook(g.mlx, on_key, &g);
	mlx_loop(g.mlx);
	mlx_terminate(g.mlx);
	close(fd);
	return (EXIT_SUCCESS);
}

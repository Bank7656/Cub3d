/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 18:39:21 by thacharo          #+#    #+#             */
/*   Updated: 2026/09/10 16:13:57 by thacharo         ###   ########.fr       */
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

int check_map_character(char **lines, int idx)
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



int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
	{
		printf("Usage: ./cub3d filename.cub\n");
		return (EXIT_FAILURE);
	}

	ft_bzero(&g, sizeof(t_game));
	if (!is_valid_filename(argv[1]))
		error_exit(&g, "Need to use .cub file");
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_exit(&g, "Cannot open .cub file");
	char **lines = read_file(fd);
	if (!lines)
		error_exit(&g, strerror(errno));
	
	int i = 0;

	while (lines[i] != NULL)
	{
		printf("[%s]\n", lines[i]);
		i++;
	}
	
	i = 0;
	while (lines[i] != NULL)
	{
		if (lines[i][0] == '\0')
		{
			i++;
			continue;		
		}
		if (is_all_values_parse(&g))
			break;
		parse_line(&g, lines[i]);

		i++;
	}
	int	map_start = i;
	if (!check_no_blank_lines(lines, map_start))
		error_exit(&g, "Map incomplete");
	if (!check_map_character(lines, map_start))
		error_exit(&g, "Invalid character");
		
	// Init constant
	g.map = dup_map(g_map);
	g.map_width = 6;
	g.map_height = 9;
	//

	if (!init_player(&g))
	{
		printf("Test\n");
		printf("Error\n");
		return (EXIT_FAILURE);
	}
	g.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!g.mlx)
		error_exit(&g, mlx_strerror(mlx_errno));
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

void	error_exit(t_game *g, const char *msg)
{
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	clear_game(g);
	exit(EXIT_FAILURE);
}

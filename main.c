/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 18:39:21 by thacharo          #+#    #+#             */
/*   Updated: 2026/09/18 15:49:28 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_cub_file(t_game *g, char *filename)
{
	int	i;
	int	fd;

	if (!is_valid_filename(filename))
		error_exit(g, "Need to use .cub file");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit(g, "Cannot open .cub file");
	g->lines = read_file(fd);
	if (!g->lines)
	{
		close(fd);
		error_exit(g, "Cannot open .cub file");
	}
	close(fd);
}

int	main(int argc, char **argv)
{
	t_game	g;
	int		map_start;

	if (argc != 2)
	{
		printf("Usage: ./cub3d filename.cub\n");
		return (EXIT_FAILURE);
	}
	ft_bzero(&g, sizeof(t_game));
	parse_cub_file(&g, argv[1]);
	map_start = map_checker(&g);
	load_map(&g, g.lines, map_start);
	if (!init_player(&g))
		error_exit(&g, "Cannot find player on a map");
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 18:39:21 by thacharo          #+#    #+#             */
/*   Updated: 2026/08/29 18:39:58 by thacharo         ###   ########.fr       */
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

int	main(void)
{
	t_game	g;

	// Init constant
	g.map = dup_map(g_map);
	g.map_width = 6;
	g.map_height = 9;
	g.ceiling = 0x87CEEBFF;
	g.floor = 0x5A4632FF;
	//

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
	return (EXIT_SUCCESS);
}

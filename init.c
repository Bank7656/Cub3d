#include "cub3d.h"

int init_data(t_cub3d *data)
{
    data->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d", false);
    if (!data->mlx)
        return (1);
    //mlx_set_window_limit(data->mlx, 1024, 768, -1, -1);
    data->image = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
	if (data->image == NULL)
        return (1);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
        return (1);
    return (0);
}

void    init_player(t_cub3d *data, char map[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (is_player_direction(map[i][j]))
            {
                data->player.x = i;
                data->player.y = j;
                data->player.direction = map[i][j];
                data->player.radius = RADIUS;
                return ;
            }
        }
    }
}


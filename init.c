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

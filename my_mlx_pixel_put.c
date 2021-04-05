#include "main.h"

void	my_mlx_pixel_put(t_map *data, int x, int y, int color)
{
	char	*dst;

	dst = data->ad + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

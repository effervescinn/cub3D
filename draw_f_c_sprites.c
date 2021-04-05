#include "main.h"

int     make_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void    draw_f_c(t_map *m)
{
	int	i;
	int	j;
	int	c_color;
	int	f_color;

	i = 0;
	c_color = make_color(m->ceil.r, m->ceil.g, m->ceil.b);
	f_color = make_color(m->floor.r, m->floor.g, m->floor.b);
	while (i < (m->winh / 2))
	{
		j = -1;
		while (++j < m->winw)
			my_mlx_pixel_put(m, j, i, c_color);
		i++;
	}
	while (i < (m->winh))
	{
		j = -1;
		while (++j < m->winw)
			my_mlx_pixel_put(m, j, i, f_color);
		i++;
	}
}

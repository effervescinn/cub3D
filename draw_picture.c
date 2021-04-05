#include "main.h"

void	draw_picture(t_map *m)
{
	double	*buffer;
	double	*spr_dist;
	int		*spr_ord;

	buffer = (double *)malloc(m->winw * sizeof(double));
	spr_dist = (double *)malloc(m->spr_l * sizeof(double));
	spr_ord = (int *)malloc(m->spr_l * sizeof(int));
	draw_f_c(m);
	draw_walls(m, &buffer);
	set_sprites(m, &spr_dist, &spr_ord);
	draw_sprs(m, spr_ord, buffer);
	free(buffer);
	free(spr_dist);
	free(spr_ord);
	if (m->screenshot == 1)
		make_screen(m);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}

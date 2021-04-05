#include "main.h"

void	set_struct(t_map *m)
{
	m->win = NULL;
	m->winh = 0;
	m->winw = 0;
	m->no = NULL;
	m->so = NULL;
	m->we = NULL;
	m->ea = NULL;
	m->s = NULL;
	m->floor.type = NULL;
	m->ceil.type = NULL;
	m->screenshot = 0;
}

void	big_res(t_map *m)
{
	int sizex;
	int sizey;

	mlx_get_screen_size(&sizex, &sizey);
	if (m->winh > sizey)
		m->winh = sizey;
	if (m->winw > (int)((double)sizey * 1.778))
		m->winw = (int)((double)sizey * 1.778);
}

int		main_image(t_map *m)
{
	m->img = mlx_new_image(m->mlx, m->winw, m->winh);
	if (m->img == NULL)
	{
		print_err(-15);
		if (m->win)
			mlx_destroy_window(m->mlx, m->win);
		free(m->sprites);
		free(m->map);
		return (-1);
	}
	m->ad = mlx_get_data_addr(m->img, &m->bpp, &m->ll, &m->end);
	m->x = (double)m->x_player + 0.5;
	m->y = (double)m->y_player + 0.5;
	return (0);
}

int		main(int argc, char **argv)
{
	char	**map;
	t_map	main_info;
	int		err;

	set_struct(&main_info);
	if ((write_info(&map, &main_info, argv) < 0))
		return (-1);
	if ((copy_map(&main_info, &map) < 0))
		return (-1);
	if ((check_conf(&main_info, &map, &err) < 0))
		return (-1);
	main_info.mlx = mlx_init();
	if ((load_images(&main_info, &err) < 0))
		return (-1);
	big_res(&main_info);
	if ((check_args(&main_info, argc, argv) < 0))
		return (-1);
	mlx_do_key_autorepeatoff(main_info.mlx);
	if ((main_image(&main_info) < 0))
		return (-1);
	draw_picture(&main_info);
	track_hooks(&main_info);
	return (0);
}

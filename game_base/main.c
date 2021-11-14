/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:41:11 by lnorcros          #+#    #+#             */
/*   Updated: 2021/04/06 17:41:12 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	sizex;
	int	sizey;

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

int		check_cub(int argc, char **argv)
{
	int	i;

	if (argc == 1)
	{
		print_err(-19);
		return (-1);
	}
	if (argc == 2)
	{
		i = ft_strlen(argv[1]);
		if (i < 5)
		{
			print_err(-20);
			return (-1);
		}
		if ((argv[1][i - 1] != 'b') && (argv[1][i - 2] != 'u') &&
		(argv[1][i - 3] != 'c') && (argv[1][i - 4] != '.'))
		{
			print_err(-20);
			return (-1);
		}
	}
	return (0);
}

int		main(int argc, char **argv)
{
	char	**map;
	t_map	m;
	int		err;

	set_struct(&m);
	if (check_cub(argc, argv) < 0)
		return (-1);
	if (write_info_check_emptys(&map, &m, argv) < 0)
		return (-1);
	if ((copy_map(&m, &map) < 0))
		return (-1);
	if ((check_conf(&m, &map, &err) < 0))
		return (-1);
	m.mlx = mlx_init();
	if ((load_images(&m, &err) < 0))
		return (-1);
	big_res(&m);
	if ((check_args(&m, argc, argv) < 0))
		return (-1);
	mlx_do_key_autorepeatoff(m.mlx);
	if ((main_image(&m) < 0))
		return (-1);
	draw_picture(&m);
	track_hooks(&m);
	return (0);
}

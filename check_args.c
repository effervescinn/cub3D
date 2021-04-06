/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:37:57 by lnorcros          #+#    #+#             */
/*   Updated: 2021/04/06 17:37:58 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	destroy_text(t_map *m)
{
	if (m->no_t.img)
		mlx_destroy_image(m->mlx, m->no_t.img);
	if (m->so_t.img)
		mlx_destroy_image(m->mlx, m->so_t.img);
	if (m->we_t.img)
		mlx_destroy_image(m->mlx, m->we_t.img);
	if (m->ea_t.img)
		mlx_destroy_image(m->mlx, m->ea_t.img);
}

void	destroy_spr(t_map *m)
{
	if (m->spr.img)
		mlx_destroy_image(m->mlx, m->spr.img);
}

int		check_args(t_map *m, int argc, char **argv)
{
	if (!(argc == 3 && !ft_strncmp(argv[2], "--save", 6)))
	{
		if (!(m->win = mlx_new_window(m->mlx, m->winw, m->winh, "cub3D")))
		{
			print_err(-16);
			free(m->sprites);
			free_arr(&(m->map));
			destroy_text(m);
			destroy_spr(m);
			return (-1);
		}
	}
	else if (argc == 3 && !ft_strncmp(argv[2], "--save", 6))
		m->screenshot = 1;
	return (0);
}

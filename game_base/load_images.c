/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:40:59 by lnorcros          #+#    #+#             */
/*   Updated: 2021/04/06 17:41:00 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	load_sprites(t_map *m)
{
	m->spr.img = mlx_xpm_file_to_image(m->mlx, m->s, &m->spr.w, &m->spr.h);
	if (m->spr.img == NULL)
		return (-14);
	m->spr.ad = get_ad(m->spr.img, &m->spr.bpp, &m->spr.ll, &m->spr.end);
	return (0);
}

int	load_textures(t_map *m)
{
	m->no_t.img = mlx_xpm_file_to_image(m->mlx, m->no, &m->no_t.w, &m->no_t.h);
	if (m->no_t.img == NULL)
		return (-13);
	m->no_t.ad = get_ad(m->no_t.img, &m->no_t.bpp, &m->no_t.ll, &m->no_t.end);
	m->so_t.img = mlx_xpm_file_to_image(m->mlx, m->so, &m->so_t.w, &m->so_t.h);
	if (m->so_t.img == NULL)
		return (-13);
	m->so_t.ad = get_ad(m->so_t.img, &m->so_t.bpp, &m->so_t.ll, &m->so_t.end);
	m->ea_t.img = mlx_xpm_file_to_image(m->mlx, m->ea, &m->ea_t.w, &m->ea_t.h);
	if (m->ea_t.img == NULL)
		return (-13);
	m->ea_t.ad = get_ad(m->ea_t.img, &m->ea_t.bpp, &m->ea_t.ll, &m->ea_t.end);
	m->we_t.img = mlx_xpm_file_to_image(m->mlx, m->we, &m->we_t.w, &m->we_t.h);
	if (m->we_t.img == NULL)
		return (-13);
	m->we_t.ad = get_ad(m->we_t.img, &m->we_t.bpp, &m->we_t.ll, &m->we_t.end);
	return (0);
}

int	load_images(t_map *m, int *err)
{
	if ((*err = load_textures(m)) < 0)
	{
		print_err(*err);
		free(m->sprites);
		free_arr(&(m->map));
		destroy_text(m);
		return (-1);
	}
	if ((*err = load_sprites(m)) < 0)
	{
		print_err(*err);
		free(m->sprites);
		free_arr(&(m->map));
		return (-1);
	}
	return (0);
}

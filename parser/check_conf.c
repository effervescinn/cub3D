/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_conf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:38:05 by lnorcros          #+#    #+#             */
/*   Updated: 2021/04/06 17:38:06 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	spr_arr(t_map *main_info, t_spr **sprites, int q)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	if (!(*sprites = (t_spr *)malloc(sizeof(t_spr) * q)))
		return (-1);
	while (i < main_info->map_len)
	{
		j = 0;
		while (j < main_info->str_len)
		{
			if (main_info->map[i][j] == '2')
			{
				(*sprites)[k].x = j + 0.5;
				(*sprites)[k].y = i + 0.5;
				k++;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	find_sprites(t_map *main_info, t_spr **sprites)
{
	int	i;
	int	j;
	int	k;
	int	quantity;

	i = 0;
	j = 0;
	k = 0;
	quantity = 0;
	while (i < main_info->map_len)
	{
		j = 0;
		while (j < main_info->str_len)
		{
			if (main_info->map[i][j] == '2')
				quantity++;
			j++;
		}
		i++;
	}
	if (spr_arr(main_info, sprites, quantity) < 0)
		return (-100);
	main_info->spr_l = quantity;
	return (0);
}

int	check_map(char ***map, t_map main_info)
{
	int	i;
	int	j;

	i = 8;
	j = 0;
	while ((*map)[i])
	{
		j = 0;
		while ((*map)[i][j])
		{
			if ((*map)[i][j] == '0' || (*map)[i][j] == '2' ||
				(*map)[i][j] == 'N' || (*map)[i][j] == 'E' ||
				(*map)[i][j] == 'S' || (*map)[i][j] == 'W')
			{
				if (flood_fill(map, j, i, main_info) < 0)
					return (-10);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_player(char **map_arr, t_map *main_info)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (map_arr[++i])
	{
		j = 0;
		while (map_arr[i][j])
		{
			if (map_arr[i][j] == 'N' || map_arr[i][j] == 'E' ||
				map_arr[i][j] == 'W' || map_arr[i][j] == 'S')
			{
				main_info->x_player = j;
				main_info->y_player = i;
				set_dir(main_info, map_arr[i][j]);
				count++;
			}
			j++;
		}
	}
	if (count != 1)
		return (-9);
	return (0);
}

int	check_conf(t_map *m, char ***map, int *err)
{
	if ((*err = check_player(m->map, m)) < 0)
	{
		print_err(*err);
		free_arr(&(m->map));
		free_arr(map);
		return (-1);
	}
	if ((*err = check_map(map, *m)) < 0)
	{
		print_err(*err);
		free_arr(&(m->map));
		free_arr(map);
		return (-1);
	}
	if ((*err = find_sprites(m, &(m->sprites))) < 0)
	{
		print_err(*err);
		free_arr(&(m->map));
		free_arr(map);
		return (-1);
	}
	free_arr(map);
	return (0);
}

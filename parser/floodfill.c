/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:40:16 by lnorcros          #+#    #+#             */
/*   Updated: 2021/04/06 17:40:18 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	flood_fill(char ***map_arr, int x, int y, t_map main_info)
{
	if (x < 0 || x > main_info.str_len ||
		y < 8 || y >= main_info.map_len + 8 ||
		!((*map_arr)[y][x] == 'N' || (*map_arr)[y][x] == 'W' ||
		(*map_arr)[y][x] == 'E' || (*map_arr)[y][x] == 'S' ||
		(*map_arr)[y][x] == '0' || (*map_arr)[y][x] == '2' ||
		(*map_arr)[y][x] == '1'))
		return (-1);
	if ((*map_arr)[y][x] == '1')
		return (1);
	if ((*map_arr)[y][x] == 'N' || (*map_arr)[y][x] == 'W' ||
		(*map_arr)[y][x] == 'E' || (*map_arr)[y][x] == 'S' ||
		(*map_arr)[y][x] == '0' || (*map_arr)[y][x] == '2')
		(*map_arr)[y][x] = '1';
	if (flood_fill(map_arr, x, y + 1, main_info) < 0)
		return (-1);
	if (flood_fill(map_arr, x + 1, y, main_info) < 0)
		return (-1);
	if (flood_fill(map_arr, x - 1, y, main_info) < 0)
		return (-1);
	if (flood_fill(map_arr, x, y - 1, main_info) < 0)
		return (-1);
	return (0);
}

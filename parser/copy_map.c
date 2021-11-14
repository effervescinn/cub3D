/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:38:41 by lnorcros          #+#    #+#             */
/*   Updated: 2021/04/06 17:38:45 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	calloc_clean(t_map *m, char ***map)
{
	int	i;

	i = 0;
	while (m->map[i])
	{
		free(m->map[i]);
		i++;
	}
	free_arr(map);
}

int		count_map_len(char **map, int i)
{
	int	map_len;

	map_len = 0;
	while (map[i])
	{
		map_len++;
		i++;
	}
	return (map_len);
}

int		longest_str(char **map)
{
	int	i;
	int	max_len;

	i = 8;
	max_len = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) > max_len)
			max_len = ft_strlen(map[i]);
		i++;
	}
	return (max_len);
}

int		copy_map(t_map *m, char ***map)
{
	int	i;

	i = -1;
	m->str_len = longest_str(*map);
	m->map_len = count_map_len(*map, 8);
	if (!(m->map = (char **)malloc((m->map_len + 1) * sizeof(char *))))
	{
		print_err(-100);
		free_arr(map);
		return (-1);
	}
	while (++i < m->map_len)
	{
		if (!(m->map[i] = ft_calloc(m->str_len + 1, 1)))
		{
			calloc_clean(m, map);
			return (-1);
		}
	}
	m->map[i] = NULL;
	i = -1;
	while (++i < m->map_len)
		ft_strcpy(m->map[i], (*map)[i + 8]);
	return (0);
}

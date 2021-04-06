/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:41:54 by lnorcros          #+#    #+#             */
/*   Updated: 2021/04/06 17:41:55 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	write_info(char ***map, t_map *m, char **argv)
{
	int		fd;
	int		err;
	char	*line;

	if (((fd = open(argv[1], O_RDWR)) < 0))
	{
		print_err(-17);
		return (-1);
	}
	if (!(m->map_str = (char *)malloc(sizeof(char))))
	{
		print_err(-100);
		return (-1);
	}
	if ((use_gnl(map, &line, &(m->map_str), fd)) < 0)
		return (-1);
	if ((err = check_info(*map, m)) < 0)
	{
		print_err(err);
		free_arr(map);
		return (-1);
	}
	return (0);
}

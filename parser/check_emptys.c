/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_emptys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:38:15 by lnorcros          #+#    #+#             */
/*   Updated: 2021/04/06 17:38:17 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	count_letters(char **map_str, int *i)
{
	int	letters;

	letters = 0;
	while (ft_isascii((*map_str)[*i]) && (*map_str)[*i] && letters < 8)
	{
		if ((*map_str)[*i] == 'R' || (*map_str)[*i] == 'N' ||
		((*map_str)[*i] == 'S' && (*map_str)[*i + 1] == 'O') ||
		(*map_str)[*i] == 'W' || (*map_str)[*i] == 'E' ||
		((*map_str)[*i] == 'S' && (*map_str)[*i + 1] == ' ') ||
		(*map_str)[*i] == 'C'
		|| (*map_str)[*i] == 'F')
		{
			letters++;
			while ((*map_str)[*i] != '\n' && (*map_str)[*i])
				(*i)++;
			while ((*map_str)[*i] == '\n')
				(*i)++;
		}
		else
			(*i)++;
	}
}

int		odd_syms(char **map_str, int *i)
{
	if (!((*map_str)[*i] == ' ' || (*map_str)[*i] == '0' ||
	(*map_str)[*i] == '1' || (*map_str)[*i] == '2' ||
	(*map_str)[*i] == 'N' || (*map_str)[*i] == 'S' ||
	(*map_str)[*i] == 'W' || (*map_str)[*i] == 'E' ||
	(*map_str)[*i] == '\n' || (*map_str)[*i] == '\0'))
	{
		print_err(-10);
		free(*map_str);
		return (-1);
	}
	return (0);
}

int		map_syms(char **map_str, int *i)
{
	return ((*map_str)[*i] == ' ' || (*map_str)[*i] == '0' ||
	(*map_str)[*i] == '1' || (*map_str)[*i] == '2' ||
	(*map_str)[*i] == 'N' || (*map_str)[*i] == 'S' ||
	(*map_str)[*i] == 'W' || (*map_str)[*i] == 'E');
}

int		check_emptys(char **map_str)
{
	int	i;

	i = 0;
	count_letters(map_str, &i);
	while (map_syms(map_str, &i))
	{
		i++;
		if ((odd_syms(map_str, &i) < 0))
			return (-1);
		if ((*map_str)[i] == '\n')
		{
			if ((*map_str)[i + 1] == '\n')
			{
				print_err(-10);
				free(*map_str);
				return (-1);
			}
			else
				i++;
		}
	}
	if ((odd_syms(map_str, &i) < 0) && ((*map_str)[i] != '\0'))
		return (-1);
	free(*map_str);
	return (0);
}

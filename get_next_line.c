/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:33:39 by lnorcros          #+#    #+#             */
/*   Updated: 2020/12/15 17:33:41 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_rest(char **rest, char **line)
{
	char	*p;

	if (*rest)
	{
		free(*line);
		if ((p = ft_strchr(*rest, '\n')))
		{
			*p = '\0';
			if (!(*line = ft_strdup(*rest)))
				return (-1);
			p++;
			ft_strcpy(*rest, p);
			return (0);
		}
		else
		{
			if (!(*line = ft_strdup(*rest)))
				return (-1);
			free(*rest);
			*rest = NULL;
		}
	}
	return (1);
}

int	write_line(char **rest, char **line, char **buf, int *c_r)
{
	char	*p;
	char	*tmp;

	if ((p = ft_strchr(*buf, '\n')))
	{
		*p = '\0';
		p++;
		if (!(*rest = ft_strdup(p)))
			return (-1);
		*c_r = 0;
	}
	tmp = *line;
	if (!(*line = ft_strjoin(tmp, *buf)))
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char *rest[1024];
	char		*buf;
	int			ret;
	int			c_r;

	if (fd < 0 || BUF_SIZE <= 0 || !line || fd > 1023 ||
	(read(fd, NULL, 0)) == -1)
		return (-1);
	if (!(*line = (char *)malloc(sizeof(char))))
		return (-1);
	if (!(buf = (char*)malloc((BUF_SIZE + 1) * sizeof(char))))
		return (-1);
	**line = '\0';
	c_r = check_rest(&rest[fd], line);
	while (c_r > 0 && (ret = read(fd, buf, BUF_SIZE > 0)))
	{
		buf[ret] = '\0';
		if ((write_line(&rest[fd], line, &buf, &c_r)) == -1)
			return (-1);
	}
	free(buf);
	if (ret < 0 || c_r < 0)
		return (-1);
	return ((ret == 0 && rest[fd] == NULL) ? 0 : 1);
}

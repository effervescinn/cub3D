/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:45:44 by lnorcros          #+#    #+#             */
/*   Updated: 2020/11/11 13:45:46 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res_str;
	size_t	s1_len;
	size_t	s2_len;
	int		i;
	int		j;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	j = 0;
	if (!(res_str = (char*)malloc((s1_len + s2_len + 1) * sizeof(*s1))))
		return (NULL);
	while (s1[i])
	{
		res_str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res_str[i] = s2[j];
		i++;
		j++;
	}
	res_str[i] = '\0';
	return (res_str);
}
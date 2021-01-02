/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:56:13 by aymaatou          #+#    #+#             */
/*   Updated: 2019/10/29 23:12:42 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

long		g_i;
long		g_number;
int			g_l_counter;

int		ft_atoi(const char *str)
{
	g_l_counter = 0;
	g_i = 0;
	g_number = 0;
	if (!str)
		ft_error("Error\nWrong or Missing Value");
	while ((str[g_i] >= 9 && str[g_i] <= 13) || (str[g_i] == 32))
		g_i++;
	while (str[g_i] != '\0')
	{
		if (g_number > 9999)
			ft_error("Error\nCheck Your Resolution input");
		if (!(str[g_i] >= 48 && str[g_i] <= 57))
			return (g_number);
		g_number = g_number * 10 + (str[g_i++] - 48);
	}
	return (g_number);
}

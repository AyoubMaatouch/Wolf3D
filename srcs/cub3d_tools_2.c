/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:44:58 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/26 15:45:00 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	ft_distance_between(double x1, double y1, double x2, double y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

void	ft_map_arg_check(char *arg)
{
	if (ft_memcmp(&arg[strlen(arg) - 4], ".cub", 5) != 0)
		ft_error("Error\nWrong File Name!\nTry Again :)\n");
}

void	ft_save_arg_check(char *arg)
{
	if (ft_memcmp(arg, "--save", 5) != 0)
		ft_error("Error\nWrong Argument Name!\nTry : --save :)\n");
}

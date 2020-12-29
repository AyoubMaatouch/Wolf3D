/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 09:58:21 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/08 18:57:24 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_while_one(char *value)
{
	int i;

	i = 0;
	while (value[i])
	{
		if (value[i] != '1' && value[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

size_t	ft_len_m(const char *str)
{
	size_t i;

	if (!str)
		ft_error("Error\nCheck Your Map");
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_check_inside(void)
{
	int i;
	int j;

	i = 1;
	if (!ft_while_one(g_file.map[0]) ||
		!ft_while_one(g_file.map[g_file.hight - 1]))
		ft_error("Error\nCheck your Map");
	while (i < g_file.hight)
	{
		j = 0;
		while (j < (int)ft_strlen(g_file.map[i]))
		{
			if (g_file.map[i][j] == '0' || g_file.map[i][j] == '2')
			{
				if (g_file.map[i][j + 1] == ' ' || g_file.map[i][j - 1] == ' ')
					ft_error("Error\nCheck your Map\n");
				if ((ft_len_m(g_file.map[i + 1]) >= ft_len_m(g_file.map[i]) &&
				(g_file.map[i + 1][j] == ' ' || g_file.map[i + 1][j] == '\0'))
				|| (g_file.map[i - 1] && g_file.map[i - 1][j] == ' '))
					ft_error("Error\nCheck your Map\n");
			}
			j++;
		}
		i++;
	}
}

void	ft_first_last_line(void)
{
	int		i;
	char	*line;

	i = 0;
	while (i < g_file.hight)
	{
		line = ft_strtrim(g_file.map[i], " ");
		if (line[0] != '1')
			ft_error("Error\nCheck Your Map\n");
		if (line[(int)ft_strlen(line) - 1] != '1')
			ft_error("Error\nCheck Your Map\n");
		if (line)
			free(line);
		i++;
	}
}

void	ft_map_error_check(void)
{
	ft_first_last_line();
	ft_check_inside();
}

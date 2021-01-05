/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:03:12 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/08 18:54:35 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#define TXY TILE + TILE / 2

void	df_player_angle(char position)
{
	g_myplayer.ishere += 1;
	if (g_myplayer.ishere > 1)
		ft_error("Error\nMORE THEN ONE PLAYER IN MAP");
	if (g_myplayer.ishere == 1)
	{
		if (position == 'N')
			g_myplayer.rotation_angle = 270.0 * (M_PI / 180);
		if (position == 'S')
			g_myplayer.rotation_angle = 90.0 * (M_PI / 180);
		if (position == 'E')
			g_myplayer.rotation_angle = 0.0 * (M_PI / 180);
		if (position == 'W')
			g_myplayer.rotation_angle = 180.0 * (M_PI / 180);
		if (position != 'N' && position != 'S'
				&& position != 'E' && position != 'W')
			ft_error("Error\nWrong Player Value.");
	}
}

void	ft_map(void)
{
	int		i;
	size_t	j;

	i = 0;
	g_sp_index = 0;
	ft_map_error_check();
	while (i < g_file.hight)
	{
		j = -1;
		while (++j < ft_strlen(g_file.map[i]))
		{
			if (iswall(j * TXY, i * TXY) == 2)
				g_sp_index++;
				// ft_get_sp_pos(j * TXY, i * TXY, g_sp_index++);
			if (ft_isalpha(g_file.map[i][j]))
			{
				df_player_angle(g_file.map[i][j]);
				g_myplayer.x = j * TXY;
				g_myplayer.y = i * TXY;
				g_file.map[i][j] = '0';
			}
		}
		i++;
	}
	if (g_myplayer.ishere == 0)
		ft_error("Error\nNO PLAYER IN MAP");
}

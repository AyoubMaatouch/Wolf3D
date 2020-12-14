#include "../cub3d.h"




void	sort(void)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = -1;
	while (++i < g_nsprite)
	{
		j = -1;
		while (++j < g_nsprite - i)
		{
			if (g_sprite[j].dst < g_sprite[j + 1].dst)
			{
				printf("B %f,%f ,%f \n",g_sprite[j].dst, g_sprite[j].x, g_sprite[j].y);
				tmp = g_sprite[j];
				g_sprite[j] = g_sprite[j + 1];
				g_sprite[j + 1] = tmp;
				printf("A %f,%f ,%f \n",g_sprite[j].dst, g_sprite[j].x, g_sprite[j].y);
			}
		}
	}
}


void	save_cordinate(int i, int j, int id)
{
	g_sprite[id].x = j * TILE + 32;
	g_sprite[id].y = i * TILE + 32;
	
}



void	get_sprite_pos(void)
{
	int i;
	int j;
	int id;

	i = 0;
	id = 0;
	while (i < g_file.hight)
	{
		j = 0;
		while (j < (int)ft_strlen(g_file.map[i]))
		{
			if (g_file.map[i][j] == '2')
			{
				save_cordinate(i, j, id);
				id++;
			}
			j++;
		}
		i++;
	}
	
}
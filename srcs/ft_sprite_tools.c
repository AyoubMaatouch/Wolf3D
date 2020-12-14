#include "../cub3d.h"

float	to_rad(float angle)
{
	angle = angle * (M_PI / 180);
	return (angle);
}

float	to_deg(float angle)
{
	angle = angle * (180 / M_PI);
	return (angle);
}

void	get_spriteimage(void)
{
	g_sptexture.img_sprite = mlx_xpm_file_to_image(g_mymlx.mlx_ptr, g_file.sprit,
			&g_sptexture.width, &g_sptexture.height);
	if (g_sptexture.img_sprite == NULL)
	{
		ft_putstr("Error\n in Sprite XPM");
		exit(1);
	}
}

void	sprite_put_pixels(int id, int i, int j)
{
	int *add;
	int a;
	int color;

	add = (int*)mlx_get_data_addr(g_sptexture.img_sprite, &a, &a, &a);
	color = add[((int)g_sptexture.width * (j * (int)g_sptexture.height /
			(int)g_sprite[id].size)) + (i * (int)g_sptexture.width /
			(int)g_sprite[id].size)];
	if (color != 0)
	{
		my_mlx_pixel_put(&g_data, g_sprite[id].x_ofst + i,
				g_sprite[id].y_ofst + j, color);
	}
}

void	draw_sprite(int id)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < g_sprite[id].size - 1)
	{
		if (g_sprite[id].x_ofst + i < 0 ||
				g_sprite[id].x_ofst + i > g_file.width_resolution)
			continue;
		if (g_sprite[id].dst > g_ray[(int)g_sprite[id].x_ofst + i].distance)
			continue;
		j = -1;
		while (++j < g_sprite[id].size - 1)
		{
			if (g_sprite[id].y_ofst + j < 0 ||
					g_sprite[id].y_ofst + j > g_file.height_resolution)
				continue;
			sprite_put_pixels(id, i, j);
		}
	}
}

void	render_sprite(int id)
{
	float angle;

	g_sprite[id].dst = (float)sqrt((g_sprite[id].x - g_myplayer.x) *
			(g_sprite[id].x - g_myplayer.x) +
			(g_sprite[id].y - g_myplayer.y) *
			(g_sprite[id].y - g_myplayer.y));
			
	angle = atan2(g_sprite[id].y - g_myplayer.y, g_sprite[id].x - g_myplayer.x);
	while (angle - g_myplayer.rotationAngle > M_PI)
		angle -= 2 * M_PI;
	while (angle - g_myplayer.rotationAngle < -M_PI)
		angle += 2 * M_PI;
	angle = angle - g_myplayer.rotationAngle;
	//angle = to_deg(angle);
	g_sprite[id].size = (g_file.width_resolution / g_sprite[id].dst) * TILE;
	g_sprite[id].y_ofst = (g_file.height_resolution / 2) - (g_sprite[id].size / 2);
	g_sprite[id].x_ofst = ((angle * g_file.width) / d2r(60)) +
		((g_file.width_resolution / 2) - (g_sprite[id].size / 2));
}
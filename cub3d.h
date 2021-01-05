/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 21:08:43 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/23 18:28:52 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** Library
*/

# include "mlx_beta/mlx.h"
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# define UP 126
# define UP_L 13
# define DOWN 125
# define DOWN_L 1
# define RIGHT 123
# define RIGHT_L 0
# define LEFT 124
# define LEFT_L 2
# define BUFFER_SIZE 1024
# define TILE 64
# define TRUE 1

typedef struct	s_inter{
	float		xinterse;
	float		yinterse;
	float		xstep;
	float		ystep;
	float		x_check;
	float		y_check;
}				t_inter;

typedef struct	s_cast{
	int			israyfacing_down;
	int			israyfacing_up;
	int			israyfacing_right;
	int			israyfacing_left;
}				t_cast;

typedef struct	s_wallhits{
	double		horizwallhit_x;
	double		horizwallhit_y;
	int			horizwallhit;
	double		vertwallhit_x;
	double		vertwallhit_y;
	int			vertwallhit;
}				t_wallhits;

typedef struct	s_ray{
	float		ray_angle;
	float		wall_hit_x;
	float		wall_hit_y;
	float		distance;
	int			was_verticale;
	int			rayfacing_up;
	int			rayfacing_down;
	int			rayfacing_right;
	int			rayfacing_left;
	int			wallhitcont;
	int			top;
	int			bottom;
	float		wallheight;

}				t_ray;

typedef struct	s_data{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_mlx{
	void		*mlx_ptr;
	void		*win_ptr;
}				t_mlx;

typedef struct	s_file{
	int			width_resolution;
	int			height_resolution;
	char		*no_t;
	char		*so_t;
	char		*we_t;
	char		*ea_t;
	char		*sprit;
	int			flor;
	int			cilng;
	char		**map;
	int			hight;
	int			width;
	int			counter;
}				t_file;

typedef struct	s_player{
	float		x;
	float		y;
	float		radius;
	int			turn_direction;
	int			walk_direction;
	int			sidewalk;
	float		rotation_angle;
	float		move_speed;
	float		rotation_speed;
	int			ishere;
	int			look;
}				t_player;

typedef struct	s_txt{
	void		*img;
	int			*data;
	int			img_width;
	int			img_height;
}				t_txt;

typedef struct	s_sprite_info{
	float		x;
	float		y;
	float		dis;
	float		y_off;
	float		x_off;
	float		size;
}				t_sprite_info;

t_inter			g_in;
t_cast			g_cast;
t_wallhits		g_wallhits;
t_ray			*g_ray;
t_data			g_data;
t_mlx			g_mymlx;
t_file			g_file;
t_player		g_myplayer;
t_txt			g_txt[5];
t_sprite_info	*g_sprite;
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
size_t			ft_strlen(const char *str);
char			*ft_strdup(char const *s1);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				get_next_line(int fd, char **line);
void			ft_get_handle(char *g_value);
int				ft_isalnum(int str);
int				ft_isalpha(int c);
int				ft_isdigit(int str);
char			*ft_strtrim(char const *s1, char const *set);
int				ft_atoi(const char *str);
char			**ft_split(char const *s, char c);
void			*ft_calloc(size_t count, size_t size);
void			*ft_bzero(void *b, size_t len);
void			ft_putstr(char *s);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_key_input(int key);
int				ft_mouse(int x, int key, int y);
//int				check(void);
int				check(int key);
void			update();
void			get_data_textures(void);
void			ft_init_mlx(void);
void			ft_init(void);
void			ft_map_handle(char *r_file, int map_size);
void			ft_openfile(char *r_file);
void			ft_get_handle(char *g_value);
void			ft_get_sprit(char *value);
void			ft_get_texture(char c, char *value);
void			ft_get_resolution(int v, int h);
void			ft_map(void);
void			draw_line(int x0, int y0, int x1, int y1, int color);
int				iswall(float x, float y);
void			cast_rays(void);
double			d2r(double angle);
void			ft_drw_player(void);
void			get_data_textures (void);
void			ft_get_data_textures_2(void);
double			normlize_anlge(double angle);
void			ft_ray(int i, double rayangle);
void			ft_horizntale_inter(double rayangle);
void			ft_verticale_inter(double rayangle);
void			ft_get_distance(int i);
double			ft_distance_between(double x1, double y1, double x2, double y2);
void			ft_wall_data(int i);
void			ft_draw_celling(int i);
int				get_side(int i);
void			ft_buildwall(int i);
void			ft_map_arg_check(char *arg);
void			ft_save_arg_check(char *arg);
void			ft_map_error_check(void);
void			*ft_error(char *str);
void			draw_sprite(int id);
void			ft_sp_data (int i);
void			ft_create_screenshot(void);
void			ft_get_sp_pos(float x, float y, int i);
int				g_sp_index;
int				g_bmp;
int				g_bonus;
void			sort(void);
char			*ft_c(char *str);
#endif

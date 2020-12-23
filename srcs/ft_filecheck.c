/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filecheck.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:49:26 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/08 18:54:17 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void ft_get_resolution(int hight, int width)
{

    int sizex;
    int sizey;
    mlx_get_screen_size(g_mymlx.mlx_ptr, &sizex, &sizey);
    g_file.height_resolution = hight;
    if (hight < 0 || width < 0)
        ft_error("Error\nNegative Resolution Values!");
    if (hight > sizey)
        g_file.height_resolution = sizey;
    else  
       g_file.height_resolution = hight;
       if (width > sizex)
        g_file.width_resolution = sizex;
    else
        g_file.width_resolution = width;
}

void ft_get_texture(char c, char *value)
{
    if (c == 'N')
    {
        if (g_file.no_t)
            ft_error("Error\nDuplicated 'NO' Texture File\n");
        else
            g_file.no_t = value;
    }
    else if (c == 'W')
    {
        if (g_file.we_t)
            ft_error("Error\nDuplicated 'WE' Texture File\n");
        else
            g_file.we_t = value;
    }
    else if (c == 'E')
    {
        if (g_file.ea_t)
            ft_error("Error\nDuplicated 'EA' Texture File\n");
        else
            g_file.ea_t = value;
    }
    else
    {
        if (g_file.so_t)
            ft_error("Error\nDuplicated 'SO' Texture File\n");
        else
            g_file.so_t = value;
    }
}

void ft_get_sprit(char *value)
{
    if (g_file.sprit)
        ft_error("Error\nDuplicated 'Sprite' File\n");
    g_file.sprit = value;
}
void ft_check_color(char *value)
{
    int i;
    int check;

    i = 0;
    check = 0;
    while (value[i])
    {
        if (!ft_isdigit(value[i]) && value[i] != ',')
            ft_error("Error\nWrong 'C' or 'F' Color Value!");
        if (value[i] == ',')
            check++;
        i++;
    }
    if (check != 2)
        ft_error("Error\nWrong 'C' or 'F' Color Value!");
}
void ft_get_cf(char c, char *value)
{
    ft_check_color(value);
    if (c == 'F')
    {
        char **temp = ft_split(value, ',');
        g_file.flor = 65536 * ft_atoi(temp[0]) + 256 * ft_atoi(temp[1]) + ft_atoi(temp[2]);
        
    }
    else
    {
        char **temp = ft_split(value, ',');
        g_file.cilng = 65536 * ft_atoi(temp[0]) + 256 * ft_atoi(temp[1]) + ft_atoi(temp[2]);
       
    }
}

void ft_get_handle(char *g_value)
{
    char **temp;

    temp = ft_split(g_value, ' ');
    if (!ft_memcmp(g_value, "R", 1))
    {
        if (temp[3])
            ft_error("Error\nPlease Check Your Resolution input!");
        ft_get_resolution(ft_atoi(temp[2]), ft_atoi(temp[1]));
    }
    if (!ft_memcmp(g_value, "WE", 2)|| !ft_memcmp(g_value, "NO", 2) || !ft_memcmp(g_value, "SO", 2) || !ft_memcmp(g_value, "EA", 2))
    {
        if (temp[2])
            ft_error("Error\nPlease Check Your Texture input!");
        ft_get_texture(g_value[0], temp[1]);
    }
    if (g_value[0] == 'F' || g_value[0] == 'C')
    {
        if (temp[2])
            ft_error("Error\nPlease Check Your 'C' or 'F' input!");
        ft_get_cf(g_value[0], temp[1]);
    }
    if (g_value[0] == 'S' && g_value[1] != 'O')
    {
        if (temp[2])
            ft_error("Error\nPlease Check Your Texture input!");
        ft_get_sprit(temp[1]);
    }
    free(temp);
}

void ft_map_handle(char *r_file, int map_size)
{
    int fd = open(r_file, O_RDONLY);
    char *line;
    int i = 0;
    g_file.hight = map_size;
    g_file.map = malloc(sizeof(char *) * (map_size + 1));
    g_file.map[map_size] = NULL;
    while ((get_next_line(fd, &line)))
    {
        if (!g_file.width || g_file.width < (int)ft_strlen(line))
            g_file.width = (int)ft_strlen(line);

        if (ft_isdigit(ft_strtrim(line, " ")[0]))
        {
            g_file.map[i] = ft_strdup(line);
            i++;
        }
        free(line);
    }
    if (ft_isdigit(ft_strtrim(line, " ")[0]))
        g_file.map[i] = ft_strdup(line);
    free(line);
}
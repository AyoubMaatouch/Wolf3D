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
#include <string.h>

void    ft_map_arg_check(char *arg)
{
    if (ft_memcmp(&arg[strlen(arg) - 4], ".cub", 5) != 0)
            ft_error("Error\nWrong File Name!\nTry Again :)\n");
}
void    ft_save_arg_check(char *arg)
{
    if (ft_memcmp(arg, "--save", 5) != 0)
            ft_error("Error\nWrong Argument Name!\nTry : --save :)\n");
} 
int ft_xmp_check(char *arg)
{
       if (ft_memcmp(&arg[strlen(arg) - 4], ".xpm", 5) != 0)
      { 
           return (0);
      }
      return (1);
}
void  ft_first_last_line(void)
{
      int i;

      i = 0;
      while (i < (int)ft_strlen(g_file.map[0]))
      {
            if (g_file.map[0][i] == '0' || g_file.map[0][i] == '2' || ft_isalpha(g_file.map[0][i]))
                  ft_error("Error\nCheck Your MAP!");
            i++;
      }
      i = 0;
         while (i < (int)ft_strlen(g_file.map[0]))
      {
            if (g_file.map[g_file.hight - 1][i] == '0' || g_file.map[g_file.hight - 1][i] == '2' 
                  || ft_isalpha(g_file.map[g_file.hight - 1][i]))
                  ft_error("Error\nCheck Your MAP!");
            i++;
      }
}

int ft_check_sides (int index)
{
      return (index);
      
}
int ft_check_up_down (int index)
{
    
      return (index);
}
void ft_map_error_check()
{
      ft_first_last_line();
      int i;

      i  = 1;
     while ( i < g_file.hight - 1)
      {
            if (!ft_check_sides(i))
                  ft_error("Error\nCheck Your MAP sides!");
            if (!ft_check_up_down(i))
                  ft_error("Error\nCheck Your MAP up down!");
            i++;
      }
}

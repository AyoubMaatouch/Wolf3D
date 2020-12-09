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
    if (strcmp(&arg[strlen(arg) - 4], ".cub") != 0)
      { 
            perror("ERROR\nWrong File Name!\nTry Again :)\n");
            exit (0);
      }
}
void    ft_save_arg_check(char *arg)
{
    if (strcmp(arg, "--save") != 0)
      { 
            perror("ERROR\nWrong Argument Name!\nTry : --save :)\n");
            exit (0);
      }
} 
int ft_xmp_check(char *arg)
{
       if (strcmp(&arg[strlen(arg) - 4], ".xpm") != 0)
      { 
           return (0);
      }
      return (1);
}

void ft_map_error_check()
{
      int i;
      i = 1;
      while (i < g_file.hight)
      {
            int j;

            j = 0;
            while ( j < (int)ft_strlen(g_file.map[i]))
            {
                  if ((g_file.map[i][j] == ' ' && g_file.map[i][j + 1] == '0'))
                  {
                        printf ("[%d] [%d] \n", i , j);
                        puts("Error\nMAP ERROR\n");
                        exit(0);
                  }
                  // if (g_file.map[i][j] == ' ' && g_file.map[i][j - 1] != '1')
                  //  {
                  //       printf ("[%d] [%d] \n", i , j);
                  //       puts("Error\nMAP ERROR\n");
                  //       exit(0);
                  // }
                  j++;
            }
            
       i++;     
      }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screenshot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:53 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/10 10:22:55 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

void creat_screenshot(void)
{
    int fd = open("first_rendered_image.bmp", O_RDWR| O_TRUNC |O_CREAT, 0666);
    int i = 0;
    short k = 0;
    int pos;
    write (fd,"BM",2 );
    i = g_file.height_resolution * g_file.width_resolution * 4 + 54;
    write(fd,&i, sizeof(int));
    write(fd, &k, 2);
    write(fd, &k, 2);
    i = 54;
    write (fd, &i, sizeof (int));
    i = 40;
    write(fd, &i, 4);
    write(fd, &g_file.width_resolution, sizeof(int));
    write(fd, &g_file.height_resolution, sizeof(int));
    k = 1;
    write(fd, &k, 2);
    k = 32;
    write (fd, &k, 2);
    i = 0;
    write (fd, &i, sizeof(int));
    write (fd, &i, sizeof(int));
    write (fd, &i, sizeof(int));
    write (fd, &i, sizeof(int));
    write (fd, &i, sizeof(int));
    write (fd, &i, sizeof(int));

    i = g_file.height_resolution - 1;
    int j = 0;

    
     while ( i >= 0)
     {
         j = 0;
         while (j < g_file.width_resolution)
         {
                pos =  (j + g_file.width_resolution * i) * 4;
              write (fd, (unsigned int *)(g_data.addr + pos)  ,4);
             j++;
         }
        i--;
     }
     close (fd);
    exit(0);
    }
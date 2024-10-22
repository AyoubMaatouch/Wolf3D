/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:02:22 by aymaatou          #+#    #+#             */
/*   Updated: 2020/11/04 19:22:11 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_bzero(void *b, size_t len)
{
	unsigned int i;

	i = 0;
	while (len > i)
	{
		((unsigned char*)b)[i] = 0;
		i++;
	}
	return (0);
}

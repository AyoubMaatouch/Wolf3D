/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdub_strjoin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:41:29 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/26 15:41:32 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		f_len;

	i = 0;
	if (s1 == NULL)
		f_len = 0;
	else
		f_len = ft_strlen(s1);
	if (!(str = (char *)malloc((f_len + ft_strlen(s2)) * sizeof(char) + 1)))
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	if (s1)
		free(s1);
	while (ft_strlen(s2))
	{
		str[i] = *s2++;
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strdup(char const *s1)
{
	char	*r_value;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	if (!(r_value = (char *)malloc(ft_strlen(s1) * sizeof(char) + 1)))
		return (NULL);
	while (s1[i])
	{
		r_value[i] = s1[i];
		i++;
	}
	r_value[i] = '\0';
	return (r_value);
}

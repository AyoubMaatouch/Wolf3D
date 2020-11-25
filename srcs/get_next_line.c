/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:53:11 by aymaatou          #+#    #+#             */
/*   Updated: 2020/11/25 10:00:29 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		s_strlen(char *r_buffer)
{
	int size;

	size = 0;
	while (r_buffer[size])
		if (r_buffer[size] == '\n')
			return (size);
		else
			size++;
	return (0);
}

char	*ft_strjoin(char   *s1, char *s2)
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	if (!(ptr = (char *)malloc((len * sizeof(char)) + 1)))
		return (NULL);
	while (len && s[j])
	{
		ptr[i++] = s[start + j++];
		len--;
	}
	ptr[i] = 0;
	return (ptr);
}
int	ft_check(char *r_buffer)
{
	int i;

	i = 0;
	while (r_buffer[i])
	{
		if (r_buffer[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_free(char **p1, char **p2, int r_value)
{
	free(*p1);
	free(*p2);
	*p1 = NULL;
	*p2 = NULL;
	if (r_value != -73)
		return (r_value > 0 ? 1 : r_value);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	int			r_value;
	char		*r_buffer;
	char		*temp;
	static char *box;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) != 0
			|| !(r_buffer = malloc(BUFFER_SIZE * sizeof(char) + 1)))
		return (-1);
	if (!box)
		box = ft_strdup("");
	while (ft_check(box) && (r_value = read(fd, r_buffer, BUFFER_SIZE)) > 0)
	{
		r_buffer[r_value] = '\0';
		box = ft_strjoin(box, r_buffer);
	}
	if (!ft_check(box))
	{
		*line = ft_substr(box, 0, s_strlen(box));
		temp = box;
		box = ft_strdup(box + s_strlen(box) + 1);
		ft_free(&temp, &r_buffer, -73);
		return (1);
	}
	*line = ft_strdup(box);
	return (ft_free(&r_buffer, &box, r_value));
}
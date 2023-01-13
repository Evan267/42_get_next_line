/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:09:02 by eberger           #+#    #+#             */
/*   Updated: 2022/12/20 14:12:05 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_rest_buff(char *s, int ls)
{
	char	*c;
	int		i;

	i = 0;
	while (s[i])
		i++;
	if (i >= 1 && ls > 0)
	{
		c = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!c)
			return (ft_clear(&s));
		ft_strlcat(c, s + ls, (BUFFER_SIZE - ls) + 1);
		ft_clear(&s);
		if (*c)
			return (c);
		else
			return (ft_clear(&c));
	}
	else
		return (ft_clear(&s));
}

char	*init_s(char **s, int fd)
{
	char	*str;

	if (fd < 0 || fd >= 10240 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (ft_clear(&(s[fd])));
	if (!s[fd])
	{
		str = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!str)
			return (NULL);
		if (read(fd, str, BUFFER_SIZE) <= 0)
			return (ft_clear(&str));
	}
	else
		str = s[fd];
	return (str);
}

void	read_s(int fd, char *s, int *ls)
{
	int	eread;

	eread = read(fd, s, BUFFER_SIZE);
	if (!eread)
		*ls = -2;
	else if (eread < BUFFER_SIZE)
	{
		while (eread < BUFFER_SIZE)
			s[eread++] = 0;
	}
}

char	*next_str(int fd, char *s, int *ls, char *str)
{
	int	lenstr;
	int	i;
	int	j;

	*ls = ft_linelen(s);
	j = 0;
	lenstr = 0;
	if (str)
	{
		while (str[lenstr])
			lenstr++;
	}
	while (s[j])
		j++;
	if (*ls > 0)
		i = lenstr + *ls + 1;
	else
		i = lenstr + j + 1;
	str = (char *)ft_realloc(str, i, lenstr);
	if (!str)
		return (NULL);
	ft_strlcat(str, s, i);
	if (*ls == -1)
		read_s(fd, s, ls);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*s[10240];
	char		*str;
	int			ls;

	ls = 0;
	str = NULL;
	s[fd] = init_s(s, fd);
	if (!s[fd])
		return (NULL);
	ls = ft_linelen(s[fd]);
	str = next_str(fd, s[fd], &ls, str);
	if (!str)
		return (ft_clear(&s[fd]));
	while (ls == -1)
	{
		str = next_str(fd, s[fd], &ls, str);
		if (!str)
			return (ft_clear(&s[fd]));
	}
	if (ls == -2 && *str == 0)
		return (ft_clear(&str));
	s[fd] = get_rest_buff(s[fd], ls);
	return (str);
}

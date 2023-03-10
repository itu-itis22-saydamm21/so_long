/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaydam <msaydam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:56:39 by msaydam           #+#    #+#             */
/*   Updated: 2022/08/03 20:57:17 by msaydam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (((char)s[i]))
		i++;
	return (i);
}

static void	delete_string(char **s)
{
	free(*s);
	*s = NULL;
}

static char	*return_line(int ret, char **s)
{
	int		line_len;
	char	*tmp;
	char	*line;

	if (ret < 0)
		return (NULL);
	else if (ret == 0 && *s == NULL)
		return (NULL);
	line_len = (int)(ft_strchr(*s, '\n') - *s);
	if (ft_strchr(*s, '\n'))
	{
		line = ft_substr(*s, 0, line_len + 1);
		tmp = ft_strdup(&(*s)[line_len + 1]);
		free(*s);
		*s = tmp;
		if ((*s)[0] == '\0')
			delete_string(s);
	}
	else
	{
		line = ft_strdup(*s);
		delete_string(s);
	}
	return (line);
}

static int	read_to_buff(int fd, char **s, char **buff)
{
	int		ret;
	char	*tmp;

	ret = read(fd, *buff, BUFFER_SIZE);
	while (ret > 0)
	{
		(*buff)[ret] = '\0';
		if (*s == NULL)
			*s = ft_strdup(*buff);
		else
		{
			tmp = ft_strjoin(*s, *buff);
			free(*s);
			*s = tmp;
		}
		if (ft_strchr(*s, '\n'))
			break ;
		ret = read(fd, *buff, BUFFER_SIZE);
	}
	free(*buff);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*s;
	int			ret;
	char		*buff;

	if (fd < 0)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || buff == NULL)
		return (NULL);
	ret = read_to_buff(fd, &s, &buff);
	return (return_line(ret, &s));
}

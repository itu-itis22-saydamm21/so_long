/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaydam <msaydam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:59:22 by msaydam           #+#    #+#             */
/*   Updated: 2022/12/26 13:59:24 by msaydam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

static size_t	ft_strlenn(const char *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

void	check_rectangle(t_complete *game)
{
	size_t	tmp;
	int		i;

	i = 0;
	tmp = ft_strlenn(game->map[0]);
	if (!tmp)
	{
		printf("Map is empty.");
		exit_point(game);
	}
	while (i < game->heightmap - 1)
	{
		if (tmp != ft_strlenn(game->map[i]))
		{
			printf("The map must be a rectangle\n");
			exit_point(game);
		}
		i++;
	}
}

static int	add_line(t_complete *game, char *line)
{
	char	**temporary;
	int		i;

	if (!line)
		return (0);
	i = 0;
	game->heightmap++;
	temporary = (char **)malloc(sizeof(char *) * (game->heightmap + 1));
	temporary[game->heightmap] = NULL;
	while (i < game->heightmap - 1)
	{
		temporary[i] = game->map[i];
		i++;
	}
	temporary[i] = line;
	if (game->map)
		free(game->map);
	game->map = temporary;
	return (1);
}

void	map_path_controls(char *str, t_complete *game)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i = i - 4;
	if (str[i] != '.'
		&& str[i + 1] != 'b'
		&& str[i + 2] != 'e'
		&& str[i + 3] != 'r')
	{
		printf("second argument should finish with '.ber'\n");
		exit_point(game);
	}		
}

int	map_reading(t_complete *game, char **argv)
{
	char	*readmap;

	map_path_controls(argv[1], game);
	game->fd = open(argv[1], O_RDONLY);
	if (game->fd < 0)
		return (0);
	while (1)
	{
		readmap = get_next_line(game->fd);
		if (!add_line(game, readmap))
			break ;
	}
	close (game->fd);
	free(readmap);
	check_rectangle(game);
	game->widthmap = ft_strlenn(game->map[0]);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaydam <msaydam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:59:01 by msaydam           #+#    #+#             */
/*   Updated: 2022/12/26 13:59:03 by msaydam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

static void	count_checker(t_complete *game, int height, int width)
{
	if (game->map[height][width] != '1' &&
		game->map[height][width] != '0' &&
		game->map[height][width] != 'P' &&
		game->map[height][width] != 'E' &&
		game->map[height][width] != 'C' &&
		game->map[height][width] != '\n')
	{
		printf("Error Here!%c\n", game->map[height][width]);
		exit_point(game);
	}
	if (game->map[height][width] == 'C')
			game->collectiblecount++;
	if (game->map[height][width] == 'P')
			game->playercount++;
	if (game->map[height][width] == 'E')
			game->exitcount++;
}

void	character_valid(t_complete *game)
{
	int	height;
	int	width;

	height = 0;
	while (height < game->heightmap)
	{
		width = 0;
		while (width <= game->widthmap - 3)
		{
			count_checker(game, height, width);
			width++;
		}
		height++;
	}
	if (!(game->playercount == 1 && game->collectiblecount >= 1
			&& game->exitcount == 1))
	{
		printf("Error\nSomething is wrong!\n");
		printf("either player, exit or collectable issue\n");
		exit_point(game);
	}
}

void	check_errors(t_complete *game)
{
	if_walls(game);
	character_valid(game);
}

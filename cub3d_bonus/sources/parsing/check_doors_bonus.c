/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_doors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:46:02 by bsuger            #+#    #+#             */
/*   Updated: 2025/11/06 11:01:07 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static int	init_doors(t_global *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game -> config.map_height)
	{
		j = 0;
		while (j < game -> config.map_width)
		{
			if (game -> config.map[i][j] == 'D')
			{
				if ((game -> config.doors_nb + 1) > MAX_DOORS)
					return (1);
				game -> config.doors[game -> config.doors_nb].tile.y = i;
				game -> config.doors[game -> config.doors_nb].tile.x = j;
				game -> config.doors[game -> config.doors_nb].index = \
													game -> config.doors_nb;
				game -> config.doors_nb++;
			}
			j++;
		}
		i++;
	}
	return (0);
}

/*
 * check if the doors is usable, we need to teleport the player
 * on a adjacent tile so we are making sure everything is fine
 * the order of tp is up, right, down, left
 */
static int	check_validity_doors(t_global *game)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < game -> config.doors_nb)
	{
		x = game -> config.doors[i].tile.x;
		y = game -> config.doors[i].tile.y;
		if (game -> config.map[y - 1][x] == '0')
			i++;
		else if (game -> config.map[y][x + 1] == '0')
				i++;
		else if (game -> config.map[y + 1][x] == '0')
				i++;
		else if (game -> config.map[y][x - 1] == '0')
				i++;
		else
			return (1);
	}
	return (0);
}

int	check_doors(t_global *game)
{
	if (init_doors(game) == 1)
		return (display_error_message("Too many doors"), 1);
	if (game -> config.doors_nb == 1)
		return (display_error_message("Only one door"), 1);
	if (check_validity_doors(game) == 1)
		return (display_error_message("At least one door is not usable"), 1);
	return (0);
}

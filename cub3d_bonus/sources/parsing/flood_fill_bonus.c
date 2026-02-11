/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuger <bsuger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:48:16 by bsuger            #+#    #+#             */
/*   Updated: 2025/10/26 15:43:22 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

int	flood_fill(t_global *game, int row, int column)
{
	if (row < 0 || column < 0 || row > game -> config.map_height
		|| column > game ->config.map_width)
		return (0);
	if (game -> config.map[row][column] == '1')
		return (0);
	if (game -> config.map[row][column] == ' ')
	{
		game -> config.map[row][column] = '1';
		if (flood_fill(game, row + 1, column) != 0)
			return (1);
		if (flood_fill(game, row, column + 1) != 0)
			return (1);
		if (flood_fill(game, row - 1, column) != 0)
			return (1);
		if (flood_fill(game, row, column - 1) != 0)
			return (1);
	}
	else
		return (1);
	return (0);
}

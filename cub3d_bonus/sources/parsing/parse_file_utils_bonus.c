/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuger <bsuger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:24:20 by bsuger            #+#    #+#             */
/*   Updated: 2025/11/06 11:10:11 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

/*
 * to check if we are not in a case of an overflow (underflow which is
 * not the right term) to be sure to compare it later 
 * with the right range [0-255]
 */

int	check_overflow_underflow(char *str)
{
	int				i;
	int				sign;
	long long int	result;

	i = 0;
	result = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		result = (result * 10) + (str[i] - '0');
		if ((result > INT_MAX) && (sign > 0))
			return (1);
		if (((result * sign) < INT_MIN) && (sign < 0))
			return (1);
		i++;
	}
	return (0);
}

/*
 * allow to verify if there is no issue with multiple sign 
 * or letters in the value of the RGB given 
*/
int	check_validity(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

/*set up some value to -1 to be able to easily check if it has been modified
 * as our calloc set everything to 0 but it's not useful in the case of
 * RGB where the ending value can be 0 by default
 * for the player by facility I do the same thing, same idea
*/
void	set_minus(t_global *game)
{
	game -> config.colors.floor = -1;
	game -> config.colors.ceiling = -1;
	game -> player.tile.y = -1;
	game -> player.tile.x = -1;
}

/*
 * set up the map the first time 
 * it happens after getting all the information without errors
 * if malloc failed we stop everything as usual
*/
int	set_up_map(t_global *game)
{
	if (game -> config.map != NULL)
		return (0);
	game -> config.map = malloc(sizeof(char *) * 1);
	if (game -> config.map == NULL)
		return (1);
	game -> config.map[0] = ft_strdup("");
	if (game -> config.map[0] == NULL)
		return (1);
	return (0);
}

/*
 * this function allow me to fill every space by 0 
 * and also update the position of the player for the minimap
*/
void	update_space_n_player(t_global *game)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = game -> config.map;
	while (i < game -> config.map_height)
	{
		j = 0;
		while (j < game -> config.map_width)
		{
			if (map[i][j] == ' ')
				map[i][j] = '0';
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				game -> player.tile.y = i;
				game -> player.tile.x = j;
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

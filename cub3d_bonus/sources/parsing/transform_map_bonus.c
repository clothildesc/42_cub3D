/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_transformation_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuger <bsuger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 14:07:03 by bsuger            #+#    #+#             */
/*   Updated: 2025/10/26 15:43:43 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	line_fill(char *str, int width)
{
	size_t	len;

	len = ft_strlen(str);
	while (len < (size_t)(width) + 1)
	{
		str[len] = ' ';
		len++;
	}
	str[len] = '\0';
}

/*
 * we go through every line and resize them with the width 
 * this width is the max width we found earlier
 * like this our map is going to be a square
 * we move the line from one to the right to have as a first char a space
 * which is very important in our startegy of flood_fill
*/
int	line_standardization(t_global *game)
{
	int		i;
	char	*temp;
	int		old_len;
	int		calculation;

	i = 0;
	while (i <= game -> config.map_height)
	{
		old_len = ft_strlen(game -> config.map[i]);
		calculation = 2 + game -> config.map_width;
		temp = ft_realloc(game -> config.map[i],
				(old_len + 1) * sizeof(char), calculation * sizeof(char));
		if (temp == NULL)
			return (1);
		game -> config.map[i] = temp;
		ft_memmove(&game -> config.map[i][1],
			game -> config.map[i], old_len + 1);
		game -> config.map[i][0] = ' ';
		i++;
	}
	return (0);
}

/*
 * We are going to transform the map to be ready for flood_fill
 * I need to add one line at the end
 * then I will go through every line to resize them 
 * at the end of this function we are ready
*/
int	map_transformation(t_global *game)
{
	int		i;
	size_t	calculation1;
	size_t	calculation2;
	char	**temp;

	i = 0;
	calculation1 = sizeof(char *) * (game -> config.map_height + 1);
	calculation2 = sizeof(char *) * (game ->config.map_height + 2);
	temp = ft_realloc(game -> config.map, calculation1, calculation2);
	if (temp == NULL)
		return (1);
	game -> config.map_height++;
	game -> config.map = temp;
	game -> config.map[game -> config.map_height] = ft_strdup(" ");
	if (game -> config.map[game ->config.map_height] == NULL)
		return (1);
	if (line_standardization(game) == 1)
		return (1);
	while (i <= game -> config.map_height)
	{
		line_fill(game -> config.map[i], game -> config.map_width);
		i++;
	}
	return (0);
}

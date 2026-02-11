/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_rgb_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuger <bsuger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 13:37:12 by bsuger            #+#    #+#             */
/*   Updated: 2025/11/05 13:35:17 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

/*
 * I exported the part where I put the value inside the 
 * array RGB if any error occur we return 1 and leave
*/
int	rgb_reading(char **temp, int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (ft_strlen(temp[i]) == 0 || check_validity(temp[i]) == 1
			|| check_overflow_underflow(temp[i]) == 1)
			return (1);
		rgb[i] = ft_atoi(temp[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (1);
		i++;
	}
	return (0);
}

/*
 * the main objective of this function is to convert the RGB given to an
 * int to be used later for the game with MLX on the right format
 * regarding the value, it's only 0 - 255 if not 
 * In this function we are working with the 
 *
*/

int	rgb_extract(t_global *game, int info, char *extract)
{
	int		i;
	int		rgb[3];
	char	**temp;

	i = rgb_cursor(extract);
	if (rgb_comma_verification(&extract[i]) == 1)
		return (1);
	temp = ft_split(&extract[i], ',');
	if (temp == NULL)
		return (1);
	if (len(temp) != 3)
		return (ft_free_tab(temp), 1);
	if (rgb_trim(temp) == 1)
		return (ft_free_tab(temp), 1);
	if (rgb_reading(temp, rgb) == 1)
		return (ft_free_tab(temp), 1);
	if (rgb_assignement(game, info, rgb) == 1)
		return (ft_free_tab(temp), 1);
	return (ft_free_tab(temp), 0);
}

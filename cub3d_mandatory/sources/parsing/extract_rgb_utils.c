/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_rgb_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuger <bsuger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 09:20:32 by bsuger            #+#    #+#             */
/*   Updated: 2025/10/27 10:59:48 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
 * function to know the lenght of a char ** NULL terminated
*/
int	len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*
 * just to verify if there is only 2 commas
 * it's not enough to check that point more security 
 * in the following parse of RGB but we are sure there
 * is an error if two commas are not here
*/
int	rgb_comma_verification(char *extract)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (extract[i])
	{
		if (extract[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (1);
	return (0);
}

/*
 * I have a char ** NULL terminated following the split with , as separator
 * Only the issue here I can have an unknown number of isspace
 * so I have to remove them because in the next steps I only want digits
 * which I will check later on
*/
int	rgb_trim(char **tab)
{
	int		i;
	char	*temp;

	i = 0;
	while (tab[i])
	{
		temp = ft_strtrim(tab[i], " \n\t\v\f\r");
		if (temp == NULL)
			return (1);
		free(tab[i]);
		tab[i] = temp;
		i++;
	}
	return (0);
}

/*
 * I am working with the unfiltered version of the line
 * extract by GNL, I need to put the cursor at the right place
 * meaning need to past the letter F or C 
*/

int	rgb_cursor(char *extract)
{
	int	i;

	i = 0;
	while (extract[i] == ' ' || extract[i] == '\t' || extract[i] == '\f'
		|| extract[i] == '\v' || extract[i] == '\r')
		i++;
	i++;
	while (extract[i] == ' ' || extract[i] == '\t' || extract[i] == '\f'
		|| extract[i] == '\v' || extract[i] == '\r')
		i++;
	return (i);
}

/*
 * From here I have made a lot of verification
 * I will just check if the value is not already full
 * meaning that I have a duplicate of a color which is not 
 * possible (an error). If everything is alright we put the 
 * value on the struct game
*/

int	rgb_assignement(t_global *game, int info, int *rgb)
{
	if (info == 4)
	{
		if (game -> config.colors.floor != -1)
			return (1);
		game -> config.colors.floor = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	}
	else
	{
		if (game -> config.colors.ceiling != -1)
			return (1);
		game -> config.colors.ceiling = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	}
	return (0);
}

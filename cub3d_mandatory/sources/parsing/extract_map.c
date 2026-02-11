/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuger <bsuger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 09:01:45 by bsuger            #+#    #+#             */
/*   Updated: 2025/10/27 10:59:38 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_in(char c, char *sep)
{
	while (*sep)
	{
		if (c == *sep)
			return (1);
		sep++;
	}
	return (0);
}

/*
 * verifiy if it's only valid char on each line I'm reading
 * in the bonus part it will change a little bit 
 * but the valid char are ; 0, 1, '\n', ' ', N, S, W, E
 * if the letter for the player appears we check if it's not already the case
 * if it is it's an error
 * I will replace '\n' by ' '
*/
int	line_verification(t_global *game, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_in(line[i], " 01NSWE\n") == 0)
			return (display_error_message("Invalid char encounter"), 1);
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
			|| line[i] == 'E')
		{
			if (game -> player.dir == 0)
				game -> player.dir = line[i];
			else
				return (display_error_message("Multiple player position"), 1);
		}
		if (line[i] == '\n')
			line[i] = ' ';
		i++;
	}
	return (0);
}

/*
 * this function will allow me to add each line to the map
 * the only verification happening here is regarding 
 * malloc, realloc and if the char in the line I'm reading are valid
*/
int	extracting_map(t_global *game, char *line)
{
	int		len;
	size_t	calculation1;
	size_t	calculation2;
	char	**temp;

	calculation1 = sizeof(char *) * (game -> config.map_height + 1);
	calculation2 = sizeof(char *) * (game -> config.map_height + 2);
	if (set_up_map(game) == 1)
		return (1);
	if (line_verification(game, line) == 1)
		return (1);
	temp = ft_realloc(game -> config.map, calculation1, calculation2);
	if (temp == NULL)
		return (1);
	game -> config.map = temp;
	game -> config.map[game -> config.map_height + 1] = line;
	game -> config.map_height++;
	len = ft_strlen(line);
	if (len > game -> config.map_width)
		game -> config.map_width = len;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_pass_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuger <bsuger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 10:51:04 by bsuger            #+#    #+#             */
/*   Updated: 2025/10/26 15:43:32 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

/*
 * This function allow me to pass all the lines
 * it will be also useful for protection during the 
 * extract of the map as the subject is clear about 
 * the fact we cannot have empty line on this part
*/
int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_in(str[i], " \n\t\v\f\r") == 0)
			return (1);
		i++;
	}
	return (0);
}

/*
 * Once I get all the informations without errors 
 * I pass all the empty lines not useful to me
*/
int	line_pass_empty(char **line, int fd)
{
	if (is_empty(*line) == 0)
	{
		while (is_empty(*line) == 0)
		{
			free(*line);
			*line = get_next_line(fd);
			if (*line == NULL)
				return (1);
		}
	}
	return (0);
}

/*
 * in this function I am going to read everything and extract
 * the map with some verification done in other parts of 
 * extracting_map() 
 * In a case of an empty line I am going to check if it's only empty
 * which I accept but if there is something else it's an error
*/
int	line_pass_nonempty(t_global *game, char **line, int fd)
{
	while (*line)
	{
		if (extracting_map(game, *line) == 1)
			return (free(*line), 1);
		*line = get_next_line(fd);
		if (*line == NULL)
			return (0);
		if (*line && is_empty(*line) == 0)
		{
			while (is_empty(*line) == 0)
			{
				free(*line);
				*line = get_next_line(fd);
				if (*line == NULL)
					return (0);
			}	
			return (display_error_message("Empty line"), free(*line), 1);
		}
	}
	return (0);
}

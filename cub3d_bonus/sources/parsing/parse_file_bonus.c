/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:31:30 by cscache           #+#    #+#             */
/*   Updated: 2025/10/28 10:31:15 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

/*
 * check if there is not already a texture which is an error as 
 * we should have only one textures per wall or object
 * check if the file is a .xpm as we only accept these kind of file
 * check also if the file with the path given is good meaning 
 * I can open it to be used
 */
int	put_data(t_global *game, int info, char *extract)
{
	int	fd;

	if (extract == NULL)
		return (display_error_message("Data not found"), 1);
	if (info >= 0 && info <= 3)
	{
		if (check_extension(extract, ".xpm") != 0)
			return (1);
		fd = opening_file(extract);
		if (fd <= 0)
			return (1);
		close(fd);
		if (game -> config.texture_paths[info] != NULL)
			return (display_error_message("Conflicting xpm"), 1);
		game -> config.texture_paths[info] = ft_strdup(extract);
		if (game -> config.texture_paths[info] == NULL)
			return (1);
	}
	else
	{
		if (rgb_extract(game, info, extract) == 1)
			return (display_error_message("Wrong colors"), 1);
	}
	return (0);
}

/*
 * main reason for this function ; the norm + didn't find a better way
 * it's just to put the value of info to be sent in put_data
*/
int	info_assignation(char *extract, int *info)
{
	if (ft_strcmp(extract, "NO") == 0)
		*info = 0;
	else if (ft_strcmp(extract, "SO") == 0)
		*info = 1;
	else if (ft_strcmp(extract, "WE") == 0)
		*info = 2;
	else if (ft_strcmp(extract, "EA") == 0)
		*info = 3;
	else if (ft_strcmp(extract, "F") == 0)
		*info = 4;
	else if (ft_strcmp(extract, "C") == 0)
		*info = 5;
	else
		return (1);
	return (0);
}

/*
 *the line is what I extract from GNL and I have to get one of the game info
 *allow me to treat the right way each informations 
 *regarding the textures or the colors for F and C
 */
int	extracting_info(t_global *game, char *line, int *i)
{
	int		info;
	char	*extract;
	char	*rgb;

	rgb = ft_strdup(line);
	if (rgb == NULL)
		return (1);
	extract = ft_strtok(line, " \f\r\t\v\n");
	if (extract == NULL && extract[0] == '\0')
		return (free(rgb), 0);
	if (info_assignation(extract, &info) == 1)
		return (free(rgb), display_error_message("invalid data"), 1);
	if (info <= 3)
	{
		if (put_data(game, info, ft_strtok(NULL, " \f\r\t\v\n")) == 1)
			return (free(rgb), 1);
		if (ft_strtok(NULL, " \f\r\t\v\n") != NULL)
			return (free(rgb), display_error_message("invalid data"), 1);
	}
	else
	{
		if (put_data(game, info, rgb) == 1)
			return (free(rgb), 1);
	}
	return (free(rgb), (*i)++, 0);
}

/*
 * first I collect the information for the map such as textures for
 * walls and colors for ceiling and floor 
 * this is why I check check for 6 informations
 * then i take everything for the map 
 */
int	reading_file(t_global *game, int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line && i < 6)
	{
		if (line[0] != '\n')
		{
			if (extracting_info(game, line, &i) == 1)
				return (get_next_line(-1), free(line), 1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (i < 6 || line == NULL)
		return (get_next_line(-1),
			display_error_message("Missing informations"), 1);
	if (line_pass_empty(&line, fd) == 1)
		return (get_next_line(-1), 1);
	if (line_pass_nonempty(game, &line, fd) == 1)
		return (get_next_line(-1), 1);
	return (get_next_line(-1), 0);
}

/*
 * function for parsing
 * first part ; read the file to collect informations and maps
 * second part ; transform the map to be squared 
 * third part ; flood_fill to be sure everything is safe
 * last part ; update the player position
*/
int	parsing_map(t_global *game, char *file)
{
	int	fd;

	set_minus(game);
	fd = opening_file(file);
	if (fd == -1)
		return (destructor_game(game), 1);
	if (reading_file(game, fd) == 1)
		return (destructor_game(game), close(fd), 1);
	close(fd);
	if (map_transformation(game) == 1)
		return (destructor_game(game), 1);
	if (flood_fill(game, 0, 0) == 1)
		return (display_error_message("Invalid map"), destructor_game(game), 1);
	update_space_n_player(game);
	if (game -> player.tile.x == -1)
		return (display_error_message("No player"), destructor_game(game), 1);
	if (check_doors(game) == 1)
		return (destructor_game(game), 1);
	if (check_textures() == 1)
		return (destructor_game(game), 1);
	return (0);
}

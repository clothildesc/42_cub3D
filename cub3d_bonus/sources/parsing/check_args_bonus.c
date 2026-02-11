/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 08:26:57 by bsuger            #+#    #+#             */
/*   Updated: 2025/10/28 14:28:10 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

int	opening_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			ft_putstr_fd("Error\nCannot open the file ; ", 2);
			ft_putstr_fd(file, 2);
			ft_putstr_fd(" no permission\n", 2);
		}
		else if (errno == ENOENT)
		{
			ft_putstr_fd("Error\nCannot open the file ; ", 2);
			ft_putstr_fd(file, 2);
			ft_putstr_fd(" do not exist\n", 2);
		}
		else
		{
			ft_putstr_fd("Error\nCannot open the file ; ", 2);
			ft_putstr_fd(file, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	return (fd);
}

/*
 * allow to check for extensions, the function is able 
 * to manage .xpm and .cub
*/
int	check_extension(char *arg, char *extension)
{
	char	*ptr;

	ptr = arg;
	if (ft_strlen(arg) < ft_strlen(extension))
	{
		ft_putstr_fd("Error\nFile must be in ", 2);
		ft_putstr_fd(extension, 2);
		ft_putstr_fd(" format\n", 2);
		return (1);
	}
	while (*ptr)
		ptr++;
	ptr -= ft_strlen(extension);
	if (ft_strcmp(extension, ptr) != 0)
	{
		ft_putstr_fd("Error\nFile must be in ", 2);
		ft_putstr_fd(extension, 2);
		ft_putstr_fd(" format\n", 2);
		return (1);
	}
	return (0);
}

int	check_args(t_global *game, int argc, char **argv)
{
	if (argc != 2)
	{
		display_error_message("Arguments must be: ./cub3d <maps>.cub");
		return (destructor_game(game), 1);
	}
	if (check_extension(argv[1], ".cub") == 1)
		return (destructor_game(game), 1);
	return (0);
}

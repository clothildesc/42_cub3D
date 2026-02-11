/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuger <bsuger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 08:23:50 by bsuger            #+#    #+#             */
/*   Updated: 2025/11/05 09:19:38 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

int	check_textures_doors(void)
{
	int	fd;

	fd = opening_file("./textures/door.xpm");
	if (fd == -1)
		return (1);
	close(fd);
	fd = opening_file("./textures/door_open_1.xpm");
	if (fd == -1)
		return (1);
	close(fd);
	fd = opening_file("./textures/door_open_2.xpm");
	if (fd == -1)
		return (1);
	close(fd);
	fd = opening_file("./textures/door_open_3.xpm");
	if (fd == -1)
		return (1);
	close(fd);
	fd = opening_file("./textures/door_open_4.xpm");
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

/*
 * function to check the additional textures from the bonus
 * check if the textures of ; door, door open
*/
int	check_textures(void)
{
	if (check_textures_doors() == 1)
		return (1);
	return (0);
}

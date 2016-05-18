/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 18:38:52 by tiboitel          #+#    #+#             */
/*   Updated: 2016/05/17 19:41:30 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Wolf3D/wolf3d.h>

int		readfile(char *file, char *buffer)
{
	int		fd;
	int		i;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		perror(strerror(errno));
		return (-1);
	}
	i = 0;
	while ((read(fd, buffer + i, sizeof(buffer))) != 0)
		i += sizeof(buffer);
	buffer[i] = '\0';
	buffer[i + 1] = '\0';
	close(fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 18:36:42 by tiboitel          #+#    #+#             */
/*   Updated: 2016/05/14 19:00:20 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Wolf3D/wolf3d.h>

t_wmap		*wolf3d_map_create()
{
	t_wmap		*map;

	if (!(map = (t_wmap *)malloc(sizeof(t_wmap))))
		return (NULL);
	map->map = NULL;
	return (map);
}

int			wolf3d_init_map(t_wmap *map, char *buffer)
{
	(void)map;
	(void)buffer;
	return (1);
}

void		wolf3d_map_destroy(t_wmap *map)
{
	if (map)
		free(map);
	map = NULL;
	(void)map;
}

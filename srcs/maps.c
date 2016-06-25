/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 18:36:42 by tiboitel          #+#    #+#             */
/*   Updated: 2016/06/25 03:29:38 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Wolf3D/wolf3d.h>

t_wmap		*wolf3d_map_create(void)
{
	t_wmap		*map;

	if (!(map = (t_wmap *)ft_memalloc(sizeof(t_wmap))))
		return (NULL);
	map->map = NULL;
	return (map);
}

int			wolf3d_map_copy(t_wmap *map, char *buffer)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			if (!(map->map[j] = (char *)ft_memalloc(sizeof(char) * (k + 1))))
				return (-1);
			strncpy(map->map[j], buffer + (i - k), k);
			map->map[j][k] = '\0';
			k = -1;
			j++;
		}
		i++;
		k++;
	}
	return (1);
}

int			wolf3d_init_map(t_wmap *map, char *buffer)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (!buffer || buffer[0] == 0)
		return (-1);
	if (!map)
		return (-1);
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			n++;
		i++;
	}
	if (!(map->map = (char **)ft_memalloc(sizeof(char *) * (n + 1))))
		return (-1);
	map->map[n] = NULL;
	wolf3d_map_copy(map, buffer);
	return (1);
}

void		wolf3d_map_destroy(t_wmap *map)
{
	int		i;

	i = 0;
	while (map->map[i])
	{
		free(map->map[i]);
		map->map[i] = NULL;
		i++;
	}
	free(map->map[i]);
	map->map[i] = NULL;
	free(map->map);
	map->map = NULL;
	free(map);
	map = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 18:36:42 by tiboitel          #+#    #+#             */
/*   Updated: 2016/05/14 19:37:29 by tiboitel         ###   ########.fr       */
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
	// Compter le nombre de \n.
	// Allouer n ligne a map->map.
	// Tant que i != de la taille du buffer
	// Compter le nombre de caracter jusqu'au prochain \n
	// Allouer et copier n caractere de buffer vers maps de x lignes
	// Deplacer curseur jusque caractere suivant le \n
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 18:36:42 by tiboitel          #+#    #+#             */
/*   Updated: 2016/06/25 01:28:25 by tiboitel         ###   ########.fr       */
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

int			wolf3d_next_map(t_wolf3d *wolf)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			buffer[100];

	wolf->player.x = 3;
	wolf->player.y = 3;
	if ((dirp = opendir("./maps")) == NULL)
	{
		perror("Couldn't open ./maps");
		return (-1);
	}
	while ((dp = readdir(dirp)) != NULL)
	{
		ft_bzero(buffer, 100);
		ft_strcat(buffer, "./maps/");
		if (dp->d_name[0] != '.')
		{
			ft_strcat(buffer, dp->d_name);
			if (ft_strcmp(buffer, wolf->map->name) != 0)
			{
				if (wolf3d_load_map(wolf, buffer))
				{
					closedir(dirp);
					return (1);
				}
			}
		}
	}
	closedir(dirp);
	free(dp);
	free(dirp);
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

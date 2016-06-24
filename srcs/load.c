/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 16:56:51 by tiboitel          #+#    #+#             */
/*   Updated: 2016/06/24 05:47:12 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Wolf3D/wolf3d.h>

static int		wolf3d_load_skybox(t_wolf3d *wolf)
{
	SDL_Surface		*skybox_bmp;
	
	skybox_bmp = NULL;
	skybox_bmp = SDL_LoadBMP("img/skybox.bmp");
	if (skybox_bmp == NULL)
		return (-1);
	wolf->skybox = SDL_CreateTextureFromSurface(wolf->renderer, skybox_bmp);
	SDL_FreeSurface(skybox_bmp);
	skybox_bmp = NULL;
	return (1);
}

int			wolf3d_load_map(t_wolf3d *wolf, char *path)
{
	char	buffer[1024];
	
	if (path == NULL || !path[0])
		return (-1);
	ft_bzero(buffer, 1024);
	if (wolf->map->map != NULL)
		wolf3d_map_destroy(wolf->map);
	if (readfile(path, buffer) == -1)
	{
		ft_putstr_fd("Unable to read intro.m3d. Programme going to quit.\n", 2);
		return (-1);
	}
	if (wolf3d_init_map(wolf->map, buffer) == -1)
	{
		ft_putstr_fd("Unable to load intro.m3d into memory. \
			Programme going to quit\n", 2);
	}
	return (1);
}

int			wolf3d_loader(t_wolf3d *wolf)
{
	wolf3d_load_map(wolf, "maps/intro.m3d");
	if (wolf3d_audio_init(wolf) == -1)
		return (-1);
	if (wolf3d_load_skybox(wolf) == -1)
		return (-1);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 16:56:51 by tiboitel          #+#    #+#             */
/*   Updated: 2016/06/21 00:06:47 by tiboitel         ###   ########.fr       */
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

int			wolf3d_loader(t_wolf3d *wolf)
{
	char	buffer[1024];

	ft_bzero(buffer, 1024);
	if (readfile("maps/wall.m3d", buffer) == -1)
	{
		ft_putstr_fd("Unable to read intro.m3d. Programme going to quit.\n", 2);
		return (-1);
	}
	if (wolf3d_init_map(wolf->map, buffer) == -1)
	{
		ft_putstr_fd("Unable to load intro.m3d into memory. \
			Programme going to quit\n", 2);
	}
	if (wolf3d_audio_init(wolf) == -1)
		return (-1);
	if (wolf3d_load_skybox(wolf) == -1)
		return (-1);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:04:46 by tiboitel          #+#    #+#             */
/*   Updated: 2016/06/01 21:25:12 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Wolf3D/wolf3d.h>

t_wolf3d	*wolf3d_create(void)
{
	t_wolf3d	*wolf;

	wolf = NULL;
	if (!(wolf = (t_wolf3d *)ft_memalloc(sizeof(t_wolf3d))))
		return (NULL);
	wolf->pWindow = NULL;
	wolf->renderer = NULL;
	wolf->frame = 0;
	wolf->map = NULL;
	wolf->map = wolf3d_map_create();
	return (wolf);
}

void		wolf3d_core(t_wolf3d *wolf)
{
	char			quit;
	SDL_Event		e;

	quit = 1;
	wolf->player.x = 3;
	wolf->player.y = 3;
	wolf->player.dirx = -1;
	wolf->player.diry = -1;
	wolf->raycaster.planex = 0.00;
	wolf->raycaster.planey = 0.66;
	while (quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 0;
			if (e.type == SDL_KEYDOWN)
				quit = 0;
		}
		wolf3d_update(wolf);
	}
}

void		wolf3d_update(t_wolf3d *wolf)
{
	unsigned int	execution_time;
	unsigned int	remaining_time;
	unsigned int	current_time;

	current_time = SDL_GetTicks();
	wolf3d_raycaster(wolf);
	wolf3d_render(wolf);
	execution_time = SDL_GetTicks() - current_time;
	remaining_time = ((int)(SCREEN_TICKS_PER_FRAME - execution_time)
			< 0) ? 0 : SCREEN_TICKS_PER_FRAME - execution_time;
	if (remaining_time > 0)
		SDL_Delay(remaining_time);
}

void		wolf3d_close(t_wolf3d *wolf)
{
	if (wolf->map)
		wolf3d_map_destroy(wolf->map);
	if (wolf)
		wolf3d_destroy_graphics(wolf);
	free(wolf);
	wolf = NULL;
	SDL_Quit();
}

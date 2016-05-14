/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 15:46:49 by tiboitel          #+#    #+#             */
/*   Updated: 2016/05/14 16:01:00 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WOLF3D_H
# define FT_WOLF3D_H

#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct		s_wolf3d
{
	SDL_Window		*pWindow;
	SDL_Renderer	*renderer;
}					t_wolf3d;

#endif

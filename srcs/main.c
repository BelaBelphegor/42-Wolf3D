/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 05:19:31 by tiboitel          #+#    #+#             */
/*   Updated: 2016/05/17 19:27:55 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Wolf3D/wolf3d.h>

int main(void)
{
	t_wolf3d		*wolf;
	if (!(wolf = wolf3d_create()))
	{
		wolf3d_close(wolf);
		return (-1);
	}
	if (!(wolf3d_init_graphics(wolf)))
	{
		wolf3d_close(wolf);
		return (-1);
	}
	wolf3d_loader(wolf);
	wolf3d_core(wolf);
	wolf3d_close(wolf);
	return (0);
}

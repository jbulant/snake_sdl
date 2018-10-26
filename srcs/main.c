/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:29:49 by jbulant           #+#    #+#             */
/*   Updated: 2018/10/25 18:05:33 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "sdl_m.h"
#include "sprite.h"

int		manage_binds(SDL_Event *event)
{
	int		r;

	r = 1;
	if (event->type == SDL_QUIT)
		r = 0;
	return (r);
}

void	frame_update(t_sprite_anim	*anim)
{
	static int	counter = 0;

	if (counter == anim->speed)
	{
		anim->frame = (anim->frame + 1) % anim->n_frame;
		counter = 0;
	}
	else
		counter++;
}

void	frame_render(t_sdl *sdl, t_sprite_anim *anim)
{
	SDL_Rect dest = {200, 200, anim->width, anim->height};
	SDL_Rect src = {
		(anim->frame % anim->x_frame) * anim->width,
		(anim->frame / anim->x_frame) * anim->height,
		anim->width, anim->height
	};
	SDL_RenderCopy(sdl->renderer, anim->texture, &src, &dest);
}

void	loop(t_sdl *sdl, t_sprite_anim	*anim)
{
	int			loop;
	SDL_Event	event;
	const Uint8	*state;

	loop = 1;
	SDL_PumpEvents();
	state = SDL_GetKeyboardState(NULL);
	while (loop == 1)
	{
		SDL_PumpEvents();
		state = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&event))
			loop = manage_binds(&event);
		if (loop != 1)
			break ;

		sdl_clear(sdl);
		frame_update(anim);
		frame_render(sdl, anim);
		sdl_render(sdl);
	}
}

int		main(void)
{
	t_sdl			sdl;
	t_sprite_anim	*anim;

	if (sdl_init(&sdl, 800, 600) == ERROR)
	{
		printf("SDL can't start\n");
		exit(1);
	}
	anim = new_sprite_anim(&sdl, "bomb.png", 100, 100);

	loop(&sdl, anim);

	free_sprite_anim(anim);
	return (0);
}

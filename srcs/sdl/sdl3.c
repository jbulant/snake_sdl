/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:18:38 by vparis            #+#    #+#             */
/*   Updated: 2018/11/02 18:27:11 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "libft.h"
#include "sdl_m.h"

static t_textures	*sdl_get_textures(void)
{
	static t_textures	textures[] = {
		{1, "textures/greystone.png", NULL},
		{2, "textures/mossy.png", NULL},
		{3, "textures/eagle.png", NULL},
		{4, "textures/wood.png", NULL},
		{5, "textures/purplestone.png", NULL},
		{6, "textures/colorstone.png", NULL},
		{-1, NULL, NULL}
	};

	return (textures);
}

static SDL_Surface	*sdl_load_texture(char *filename)
{
	SDL_Surface	*surf;

	if ((surf = IMG_Load(filename)) == NULL)
	{
		ft_putstr("Error : can't load texture from ");
		ft_putendl(filename);
		return (NULL);
	}
	return (surf);
}

SDL_Surface			*sdl_get_texture(int id)
{
	t_textures	*textures;

	textures = sdl_get_textures();
	return (textures[id].texture);
}

int					sdl_init_textures(void)
{
	t_textures	*textures;
	int			i;

	textures = sdl_get_textures();
	i = 0;
	while (textures[i].id != -1)
	{
		if ((textures[i].texture = sdl_load_texture(textures[i].filename))
			== NULL)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

void				sdl_destroy_textures(void)
{
	t_textures	*textures;
	int			i;

	textures = sdl_get_textures();
	i = 0;
	while (textures[i].id != -1)
	{
		SDL_FreeSurface(textures[i].texture);
		i++;
	}
}

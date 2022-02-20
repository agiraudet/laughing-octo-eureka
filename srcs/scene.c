/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 21:55:43 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/20 19:15:30 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boids.h"

void	scene_del(t_scene *sc)
{
	SDL_DestroyRenderer(sc->ren);
	SDL_DestroyWindow(sc->win);
	SDL_Quit();
	free(sc);
}

t_scene	*scene_new(t_settings *set)
{
	t_scene	*sc;
	Uint32	flags;

	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
		return (0);
	sc = (t_scene *)malloc(sizeof(t_scene));
	if (!sc)
	{
		SDL_Quit();
		return (0);
	}
	if (set->fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;
	else
		flags = 0;
	sc->win = SDL_CreateWindow("BOIIIIDS", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, set->sc_wd, set->sc_hg, flags);
	sc->ren = SDL_CreateRenderer(sc->win, -1, 0);
	if (!sc->win || !sc->ren)
	{
		SDL_Quit();
		free(sc);
		return (0);
	}
	sc->wd = set->sc_wd;
	sc->hg = set->sc_hg;
	sc->time = timer_new();
	sc->set = set;
	return (sc);
}

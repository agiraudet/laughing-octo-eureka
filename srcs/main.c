/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 21:42:42 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/20 20:14:07 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boids.h"
#include "data.h"

void	input(t_scene *sc, int keysym)
{
	if (keysym == SDLK_q && sc->set->speed_limit > 0.)
		sc->set->speed_limit -= 1.;
	if (keysym == SDLK_w)
		sc->set->speed_limit += 1.;
}

int	play(t_scene *sc)
{
	SDL_Event	event;
	t_boid		**boids;

	boids = boids_nnew(sc->set->nb_boids, sc->wd, sc->hg);
	data_init(sc, boids);
	timer_update(sc->time);
	stream_start();
	while (1)
	{
		render_all(sc, boids);
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			break ;
		if (event.type == SDL_KEYDOWN)
			input(sc, event.key.keysym.sym);
		boid_update(sc, boids);
	}
	//boids_del(boids);
	return (0);
}

int main(int argc, char **argv)
{
	t_scene		*sc;
	t_settings	*set;

	set = set_new(argc, argv);
	sc = scene_new(set);
	if (!sc)
		return (1);
	calcul_randseed();
	play(sc);
	scene_del(sc);
	return (0);
}

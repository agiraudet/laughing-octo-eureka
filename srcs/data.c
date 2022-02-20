/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:19:09 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/20 16:35:09 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boids.h"

t_boid	**data_boids(t_boid **get_boids)
{
	static t_boid	**boids = 0;

	if (get_boids)
		boids = get_boids;
	return (boids);
}

t_scene	*data_scene(t_scene	*get_sc)
{
	static t_scene	*sc;

	if (get_sc)
		sc = get_sc;
	return (sc);
}

void	data_init(t_scene *sc, t_boid **boids)
{
	data_boids(boids);
	data_scene(sc);
}

void	data_screen_size(t_pos *size)
{
	t_scene	*sc;

	size->x = 0.;
	size->y = 0.;
	sc = data_scene(0);
	if (!sc)
		return ;
	size->x = sc->wd;
	size->y = sc->hg;
}

int	data_nb_boids(void)
{
	t_boid	**boids;
	int		i;

	boids = data_boids(0);
	if (!boids)
		return (0);
	i = 0;
	while (boids[i])
		i++;
	return (i);
}

void	data_pos_average(t_pos *average)
{
	t_boid	**boids;
	int		i;

	average->x = -1.;
	average->y = -1.;
	boids = data_boids(0);
	if (!boids)
		return ;
	average->x = 0.;
	average->y = 0.;
	i = 0;
	while (boids[i])
	{
		average->x += boids[i]->pos.x;
		average->y += boids[i]->pos.y;
		i++;
	}
	if (i)
	average->x /= (double)i;
	average->y /= (double)i;
}

void	data_pos_single(t_pos *single, int id)
{
	t_boid	**boids;

	single->x = -1.;
	single->y = -1.;
	if (id >= data_nb_boids())
		return ;
	boids = data_boids(0);
	if (!boids)
		return ;
	single->x = boids[id]->pos.x;
	single->y = boids[id]->pos.y;
}

void	data_boids_sector(int nb_sector_x, int nb_sector_y, int id, t_pos *pos)
{
	t_boid	**boids;
	t_scene	*sc;
	int		sector_size_x;
	int		sector_size_y;

	pos->x = -1.;
	pos->y = -1.;
	boids = data_boids(0);
	if (!boids)
		return ;
	sc = data_scene(0);
	if (!sc || id >= data_nb_boids())
		return ;
	sector_size_x = sc->wd / nb_sector_x;
	sector_size_y = sc->wd / nb_sector_y;
	pos->x = (int)boids[id]->pos.x / (int)sector_size_x;
	pos->y = (int)boids[id]->pos.y / (int)sector_size_y;
}

void	data_set_color(int id, Uint8 r, Uint8 g, Uint8 b)
{
	t_boid	**boids;

	boids = data_boids(0);
	if (!boids)
		return ;
	if (id >= data_nb_boids())
		return ;
	boids[id]->color[0] = r;
	boids[id]->color[1] = g;
	boids[id]->color[2] = b;
}

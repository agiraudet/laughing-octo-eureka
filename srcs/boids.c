/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boids.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 22:45:52 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/20 16:35:59 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boids.h"

t_boid	*boids_new(t_pos *pos, t_pos *dir)
{
	t_boid	*boid;

	boid = (t_boid *)malloc(sizeof(t_boid));
	if (!boid)
		return (0);
	boid->pos.x = pos->x;
	boid->pos.y = pos->y;
	boid->dir.x = dir->x;
	boid->dir.y = dir->y;
	boid->color[0] = 0xFF;
	boid->color[1] = 0x00;
	boid->color[2] = 0x00;
	return (boid);
}

void	boids_del(t_boid **boids)
{
	int	i;

	i = 0;
	while (boids[i])
		free(boids[i++]);
	free(boids);
}

void	boids_randomize(t_pos *pos, t_pos *dir, int wd, int hg)
{
	calcul_randpos(pos, 0, wd, 0, hg);
	dir->x = calcul_randf(-1., 1.);
	dir->y = calcul_randf(-1., 1.);
}

t_boid	**boids_nnew(int n, int wd, int hg)
{
	t_boid	**boids;
	t_pos	pos;
	t_pos	dir;
	int		i;

	boids = (t_boid **)malloc(sizeof(t_boid *) * (n + 1));
	if (!boids)
		return (0);
	i = 0;
	while (i < n)
	{
		boids_randomize(&pos, &dir, wd, hg);
		boids[i++] = boids_new(&pos, &dir);
	}
	boids[i] = 0;
	return (boids);
}

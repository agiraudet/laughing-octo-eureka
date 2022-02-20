/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boids.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 21:53:29 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/20 20:23:07 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOIDS_H
# define BOIDS_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_mixer.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>

typedef struct	s_timer
{
	uint32_t	start_time;
	int			relative_time;
	int			frames;
	double		avg_fps;
}				t_timer;

typedef struct	s_settings
{
	int		nb_boids;
	int		fullscreen;
	int		sc_wd;
	int		sc_hg;
	int		margin;
	int		debug_fps;
	int		fps_max;
	int		debug_visual_range;
	int		boid_wd;
	int		boid_hg;
	double	boid_speed;
	double	turn_factor;
	double	boid_visual_range;
	double	centering_factor;
	double	min_dist;
	double	avoid_factor;
	double	matching_factor;
	double	speed_limit;
}				t_settings;


typedef struct	s_scene
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	t_timer			*time;
	t_settings		*set;
	int				wd;
	int				hg;
}				t_scene;

typedef struct	s_pos
{
	double	x;
	double	y;
}				t_pos;


typedef struct	s_boid
{
	t_pos	pos;
	t_pos	dir;
	Uint8	color[3];
}				t_boid;


t_timer	*timer_new(void);
void	timer_update(t_timer *tm);
void	timer_capfps(t_settings *set, t_timer *tm);
void	timer_capbpm(t_timer *tm, size_t bpm);

t_boid	**boids_nnew(int n, int wd, int hg);
void	boids_del(t_boid **boids);
void boid_update(t_scene *sc, t_boid **boid);

void    render_all(t_scene *sc, t_boid **boids);

void    scene_del(t_scene *sc);
t_scene	*scene_new(t_settings *set);

double calcul_dist(t_pos *pos_a, t_pos *pos_b);
int    calcul_rand(int min, int max);
double	calcul_randf(double min, double max);
void   calcul_randseed(void);
void	calcul_randpos(t_pos *pos, int xmin, int xmax, int ymin, int ymax);
t_settings	*set_new(int argc, char **argv);

int	stream_start();


void	sound_loop_thread(void);
#endif

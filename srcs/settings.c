/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:52:26 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/19 17:59:18 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boids.h"

void	set_default(t_settings	*set)
{
	set->nb_boids = 100;
	set->fullscreen = 0;
	set->sc_wd = 720;
	set->sc_hg = 480;
	set->margin = 50.;
	set->debug_fps = 0;
	set->fps_max = 60;
	set->debug_visual_range = 0;
	set->boid_wd = 5;
	set->boid_hg = 5;
	set->boid_speed = 0.5;
	set->turn_factor = 1.;
	set->boid_visual_range = 75.;
	set->centering_factor = 0.005;
	set->min_dist = 20.;
	set->avoid_factor = 0.05;
	set->matching_factor = 0.05;
	set->speed_limit = 10.;
}

void	set_size(t_settings *set, const char *arg)
{
	int	i;
	char	*w;
	char	*h;

	i = 0;
	while (arg[i] && arg[i] != 'x')
		i++;
	if (!arg[i])
	{
		fprintf(stderr, "%s: invalid size, need WIDTHxHEIGHT\n", arg);
		exit (1);
	}
	w = strndup(arg, i);
	h = strdup(arg + i + 1);
	set->sc_wd = atoi(w);
	set->sc_hg = atoi(h);
	free(w);
	free(h);
}

void	set_boid_size(t_settings *set, const char *optarg)
{
	int	size;

	size = atoi(optarg);
	set->boid_hg = size;
	set->boid_wd = size;
}

int		help(void)
{
	printf("Options:\n  -n [n]\tnumber_of_boids\n  -f\t\tfullscreen\n  -s [WDxHG]\twindow size\n  -S [n]\tboids size\n  -t [n]\tturn factor\n  -v [n]\t centering factor\n  -c [n]\tcentering factor\n  -d [n]\tavoiding distance\n  -a [n]\tavoid factor\n  -m [n]\t matching factor\n  -l [n]\tspeed limit\n  -h\t\tprint this help and exit\n\n");
	return (0);
}

void	set_opt(t_settings *set, int argc, char **argv)
{
	int	option;

	while ((option = getopt(argc, argv, ":n:fs:S:t:v:c:d:a:m:l:Dh")) != -1)
	{
		if (option == 'n')
			set->nb_boids = atoi(optarg);
		else if (option == 'f')
			set->fullscreen = 1;
		else if (option == 's')
			set_size(set, optarg);
		else if (option == 'S')
			set_boid_size(set, optarg);
		else if (option == 't')
			set->turn_factor = atof(optarg);
		else if (option == 'v')
			set->boid_visual_range = atof(optarg);
		else if (option == 'c')
			set->centering_factor = atof(optarg);
		else if (option == 'd')
			set->min_dist = atof(optarg);
		else if (option == 'a')
			set->avoid_factor = atof(optarg);
		else if (option == 'm')
			set->matching_factor = atof(optarg);
		else if (option == 'l')
			set->speed_limit = atof(optarg);
		else if (option == 'D')
		{
			set->debug_fps = 1;
			set->debug_visual_range = 1;
		}
		else if (option == 'h')
			exit(help());
		else if (option == ':')
			exit(printf("need values\n"));
		else
			exit(printf("unknow option\n"));
	}
}

t_settings	*set_new(int argc, char **argv)
{
	t_settings	*set;

	set = (t_settings *)malloc(sizeof(t_settings));
	if (!set)
	{
		fprintf(stderr, "Could not create settings, aborting.\n");
		exit(1);
	}
	set_default(set);
	if (argc > 1)
		set_opt(set, argc, argv);
	return (set);
}

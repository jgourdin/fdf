/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 01:43:09 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/04 01:39:25 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			k_hook(int keycode, t_fdf *env)
{
	if (keycode == ESC)
		exit(42);
	else if (keycode == LEFT || keycode == RIGHT
			|| keycode == UP || keycode == DOWN)
	{
		if (keycode <= 124)
			keycode == LEFT ? BASEX -= 10 : (BASEX += 10);
		else
			keycode == UP ? BASEY -= 10 : (BASEY += 10);
	}
	else if (keycode == PLUS || keycode == MINUS)
		keycode == PLUS ? ZOOM += 5 : (ZOOM -= 5);
	else if (keycode == AP || keycode == AM)
		keycode == AP ? ANGLE += 10 : (ANGLE -= 10);
	else if (keycode == 8)
	{
		COLORTMP = COLORTMP + 1100000;
		COLORTMP2 = COLORTMP2 - 1100000;
	}
	else
		return (0);
	mlx_destroy_image(INIT, IMAGE);
	lauchfactory(env);
	return (0);
}

void		init(t_fdf **env)
{
	(*env)->mlx.init = mlx_init();
	(*env)->options.zoom = 5;
	(*env)->options.colortmp = 0xFFFFFF;
	(*env)->largeur = 2300;
	(*env)->hauteur = 1300;
	(*env)->options.angle = 20;
	(*env)->basex = 1;
	(*env)->basey = 1;
	(*env)->options.zed = 2;
	(*env)->mlx.window = mlx_new_window((*env)->mlx.init, (*env)->largeur,
			(*env)->hauteur, "Fdf");
	while ((*env)->xmax * (*env)->ymax * (*env)->options.zoom <=
			((*env)->largeur * (*env)->hauteur) / (*env)->options.zoom / 4)
		(*env)->options.zoom = (*env)->options.zoom + 1;
	(*env)->basex = ((*env)->largeur - ((*env)->xmax * (*env)->options.zoom));
	(*env)->basey = ((*env)->hauteur - ((*env)->ymax *
				(*env)->options.zoom)) / 2;
}

int			*atoi_feed(char **line, t_fdf **env)
{
	int		*out;
	int		y;

	y = 0;
	while (line[y])
		y++;
	if ((*env)->xmax && y < (*env)->xmax)
	{
		return (NULL);
	}
	(*env)->xmax = y;
	if (!(out = (int *)malloc(sizeof(int) * (y + 1))))
		return (NULL);
	y = 0;
	while (line[y])
	{
		ft_atoi(line[y]) > (*env)->zmax ? (*env)->zmax = ft_atoi(line[y]) : 0;
		ft_atoi(line[y]) > (*env)->zmin ? (*env)->zmin = ft_atoi(line[y]) : 0;
		*out++ = ft_atoi(line[y]);
		y++;
	}
	*out = '\0';
	out = out - y;
	return (out);
}

int			count(t_fdf **env, char *file)
{
	int		i;
	char	buff[BUFF_SIZE + 1];

	i = 0;
	(*env)->rd = 0;
	if (((*env)->fd = open(file, O_RDONLY)) < 0)
	{
		ft_putstr("Not valid Argument");
		exit(42);
	}
	while (((*env)->rd = read((*env)->fd, buff, BUFF_SIZE)))
	{
		buff[(*env)->rd] = '\0';
		(*env)->c = 0;
		while (buff[(*env)->c])
		{
			if (buff[(*env)->c] == '\n')
				i++;
			(*env)->c++;
		}
	}
	(*env)->ymax = i;
	if (!((*env)->map.map = (int **)malloc(sizeof(int *) * (i + 1))))
		return (0);
	return (i);
}

int			main(int argc, char **argv)
{
	t_fdf	*env;
	char	*line;
	int		i;

	if (!(env = (t_fdf *)malloc(sizeof(t_fdf))))
		return (0);
	if (argc == 2)
	{
		count(&env, argv[1]);
		env->zmax = 0;
		env->zmin = 0;
		env->map.fd = open(argv[1], O_RDONLY);
		while ((get_next_line(env->map.fd, &line)) > 0)
		{
			if (!(*(MAP)++ = atoi_feed(ft_strsplit(line, ' '), &env)))
				break ;
		}
		MAP = MAP - env->ymax;
		init(&env);
		lauchfactory(env);
		mlx_hook(WIN, 2, 0, k_hook, env);
		mlx_loop(INIT);
	}
	else
		ft_putstr("Error : Need One Argument");
}

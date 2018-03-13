/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 01:42:52 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/04 01:34:36 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "./minilibx_macos/mlx.h"
# include "./libft/libft.h"

# define INIT env->mlx.init
# define WIN env->mlx.window
# define WIDTH env->largeur
# define HEIGHT env->hauteur
# define DATA env->mlx.data
# define IMAGE env->mlx.image
# define BPP env->mlx.bpp
# define SIZE env->mlx.size_line
# define ENDIAN env->mlx.endian
# define ZOOM env->options.zoom
# define HORIZ env->options.horiz
# define VERTI env->options.verti
# define MAP env->map.map
# define DATA env->mlx.data
# define COLOR env->options.color
# define COS cos(M_PI * env->options.angle / 180)
# define SIN sin(M_PI * env->options.angle / 180)
# define X0 env->x0
# define X1 env->x1
# define Y0 env->y0
# define Y1 env->y1
# define XMAX env->xmax
# define YMAX env->ymax
# define BASEX env->basex
# define BASEY env->basey
# define ZMAX env->zmax
# define DX env->calc.dx
# define SX env->calc.sx
# define DY env->calc.dy
# define SY env->calc.sy
# define ERR env->calc.err
# define ZED env->options.zed
# define ANGLE env->options.angle
# define COLORTMP env->options.colortmp
# define COLORTMP2 env->options.colortmp2
# define AP 81
# define AM 75
# define ESC 53
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define PLUS 69
# define MINUS 78

typedef struct	s_mlx
{
	void		*init;
	void		*window;
	void		*image;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_mlx;

typedef struct	s_options
{
	int			horiz;
	int			verti;
	int			zoom;
	int			angle;
	int			color;
	int			zed;
	int			colortmp;
	int			colortmp2;
}				t_options;

typedef struct	s_calc
{
	int			dx;
	int			sx;
	int			dy;
	int			sy;
	int			err;
	int			e2;
}				t_calc;

typedef struct	s_map
{
	int			nbr_lines;
	int			fd;
	int			**map;
}				t_map;

typedef struct	s_fdf
{
	int			largeur;
	int			hauteur;
	int			xmax;
	int			ymax;
	int			zmax;
	int			xmin;
	int			ymin;
	int			zmin;
	int			basex;
	int			basey;
	int			x0;
	int			rd;
	int			fd;
	int			c;
	int			y0;
	int			x1;
	int			y1;
	t_mlx		img;
	t_map		map;
	t_options	options;
	t_mlx		mlx;
	t_calc		calc;
}				t_fdf;

void			mlx_pixel_image(t_fdf *env, int x, int y);
void			calc_line(t_fdf *env);
int				dif_point(int x, int y, t_fdf *env);
int				lauchfactory(t_fdf *env);
int				*atoi_feed(char **line, t_fdf **env);
void			init(t_fdf **env);
int				count(t_fdf **env, char *file);
int				main(int argc, char *argv[]);
void			ft_info(t_fdf *env);
int				k_hook(int keycode, t_fdf *env);

#endif

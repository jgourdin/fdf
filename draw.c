/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 04:03:03 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/04 01:20:36 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		mlx_pixel_image(t_fdf *env, int x, int y)
{
	int		i;

	i = (x * (BPP / 8) + (y * SIZE));
	DATA[i] = COLOR;
	DATA[i + 1] = COLOR >> 8;
	DATA[i + 2] = COLOR >> 16;
}

void		calc_line(t_fdf *env)
{
	DX = abs(X1 - X0);
	SX = X0 < X1 ? 1 : -1;
	DY = abs(Y1 - Y0);
	SY = Y0 < Y1 ? 1 : -1;
	ERR = (DX > DY ? DX : -DY) / 2;
	while (42)
	{
		X0 < WIDTH && (X0 > 1) && Y0 < HEIGHT && (Y0 > 1)
			? mlx_pixel_image(env, X0, Y0) : 0;
		if (X0 == X1 && Y0 == Y1)
			break ;
		env->calc.e2 = ERR;
		if (env->calc.e2 > -DX)
		{
			ERR -= DY;
			X0 += SX;
		}
		if (env->calc.e2 < DY)
		{
			ERR += DX;
			Y0 += SY;
		}
	}
}

int			dif_point(int x, int y, t_fdf *env)
{
	if (x < XMAX)
	{
		X0 = (x * ZOOM) * COS - (y * ZOOM) * SIN + BASEX;
		X1 = ((x + 1) * ZOOM) * COS - (y * ZOOM) * SIN + BASEX;
		Y0 = (y * ZOOM) * COS + (x * ZOOM) * SIN / ZED
			+ BASEY - (MAP[y][x] * ZOOM / ZED);
		Y1 = (y * ZOOM) * COS + ((x + 1) * ZOOM) * SIN / ZED
			+ BASEY - (MAP[y][x + 1] * ZOOM / ZED);
		calc_line(env);
	}
	if (y < YMAX - 1)
	{
		X0 = (x * ZOOM) * COS - (y * ZOOM) * SIN + BASEX;
		X1 = (x * ZOOM) * COS - ((y + 1) * ZOOM) * SIN + BASEX;
		Y0 = (y * ZOOM) * COS + (x * ZOOM) * SIN / ZED + BASEY -
			(MAP[y][x] * ZOOM / ZED);
		Y1 = ((y + 1) * ZOOM) * COS + (x * ZOOM) * SIN / ZED
			+ BASEY - (MAP[y + 1][x] * ZOOM / ZED);
		calc_line(env);
	}
	return (0);
}

int			lauchfactory(t_fdf *env)
{
	int		x;
	int		y;

	y = 0;
	IMAGE = mlx_new_image(INIT, WIDTH, HEIGHT);
	DATA = mlx_get_data_addr(IMAGE, &BPP, &SIZE, &ENDIAN);
	while (y < YMAX)
	{
		x = 0;
		while (x <= XMAX)
		{
			if (MAP[y][x] == (ZMAX))
				COLOR = COLORTMP2;
			else
				COLOR = COLORTMP;
			dif_point(x, y, env);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(INIT, WIN, IMAGE, 0, 0);
	ft_info(env);
	return (0);
}

void		ft_info(t_fdf *env)
{
	mlx_string_put(INIT, WIN, 50, 50, 0xFFFFFF, "----MENU----");
	mlx_string_put(INIT, WIN, 50, 70, 0xFFFFFF, "------------");
	mlx_string_put(INIT, WIN, 50, 90, 0xFFFFFF, "----MOVE:---");
	mlx_string_put(INIT, WIN, 50, 110, 0xFFFFFF, "--UP  DOWN--");
	mlx_string_put(INIT, WIN, 50, 130, 0xFFFFFF, "-LEFT RIGHT-");
	mlx_string_put(INIT, WIN, 50, 150, 0xFFFFFF, "------------");
	mlx_string_put(INIT, WIN, 50, 170, 0xFFFFFF, "---ZOOM:----");
	mlx_string_put(INIT, WIN, 50, 190, 0xFFFFFF, "--  +  -  --");
	mlx_string_put(INIT, WIN, 50, 210, 0xFFFFFF, "---ANGLE:---");
	mlx_string_put(INIT, WIN, 50, 230, 0xFFFFFF, "--- =  / ---");
	mlx_string_put(INIT, WIN, 50, 250, 0xFFFFFF, "-COLOR-YOLO:");
	mlx_string_put(INIT, WIN, 50, 270, 0xFFFFFF, "---- C -----");
	mlx_string_put(INIT, WIN, 50, 290, 0xFFFFFF, "------------");
}

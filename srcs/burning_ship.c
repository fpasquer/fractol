/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 10:30:33 by fpasquer          #+#    #+#             */
/*   Updated: 2017/02/28 23:11:15 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fractol.h"

static t_pixel				get_pixel(t_fractol **f)
{
	double					curent_x;
	double					curent_y;
	t_pixel					p;

	ft_bzero(&p,sizeof(p));
	if (f != NULL && *f != NULL)
	{
		curent_x = get_curent_position(-1.95, 1.1, (*f)->x_mouse, WIDTH);
		curent_y = get_curent_position(-1.745, 0.5, (*f)->y_mouse, HEIGHT);
		p.x1 = (*f)->zoom * (-1.95 - curent_x) + curent_x;
		p.x2 = (*f)->zoom * (1.1 - curent_x) + curent_x;
		p.y1 = (*f)->zoom * (-1.745 - curent_y) + curent_y;
		p.y2 = (*f)->zoom * (0.5 - curent_y) + curent_y;
		p.zoom_x = WIDTH / (p.x2 - p.x1);
		p.zoom_y = HEIGHT / (p.y2 - p.y1);
	}
	return (p);
}

static double				ft_abs_double(double nb)
{
	return ((nb < 0) ? nb * -1.0 : nb);
}

static int					init_burning_ship(t_pixel *p, int x, int y,
		t_fractol **f)
{
	if (f == NULL || *f == NULL || p == NULL)
		return (false);
	p->c_r = (double)x /
			(p->zoom_x * (1.0 + (double)(*f)->zoom / 100.0)) + p->x1;
	p->c_i = (double)y /
			(p->zoom_y * (1.0 + (double)(*f)->zoom / 100.0)) + p->y1;
	p->z_r = 0.0;
	p->z_i = 0.0;
	p->i = 0.0;
	return (true);
}

static int					draw_pixel_burning_ship(t_fractol **f, t_pixel p,
		int x_tab, int y_tab)
{
	if (f == NULL || *f == NULL)
		return (ERROR);
	while (1)
	{
		p.tmp = p.z_r;
		p.z_r = p.z_r * p.z_r - p.z_i * p.z_i + p.c_r;
		p.z_i = 2 * ft_abs_double(p.z_i * p.tmp) + p.c_i;
		p.i = p.i + 1;
		if (!(p.z_r * p.z_r + p.z_i * p.z_i < 4 && p.i < (*f)->iter))
			break ;
	}
	if (p.i == (*f)->iter)
		return (turn_on_pixel(f, x_tab, y_tab, 0x0));
	if (turn_on_pixel(f, x_tab, y_tab, ft_rgba(CL((*f)->red), CL((*f)->green),
			CL((*f)->blue), 0)) == ERROR)
		return (ERROR);

	return (false);
}

int							draw_burning_ship(int x_mouse, int y_mouse,
		t_fractol **f)
{
	int						x_tab;
	int						y_tab;
	t_pixel					p;

	if ((*f)->data == NULL)
		return (false);
	p = get_pixel(f);
	(*f)->x = x_mouse;
	(*f)->y = y_mouse;
	y_tab = 0;
	while (y_tab < HEIGHT)
	{
		x_tab = 0;
		while (x_tab < WIDTH)
		{
			if (init_burning_ship(&p, x_tab, y_tab, f) == false)
				return (ERROR);
			if (draw_pixel_burning_ship(f, p, x_tab, y_tab) == ERROR)
				return (ERROR);
			x_tab++;
		}
		y_tab++;
	}
	(*f)->fractal = BURNING_SHIP;
	return (end_loop_fractol(f, "burning_ship", x_mouse, y_mouse));
}

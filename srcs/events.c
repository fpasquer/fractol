/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 10:58:54 by fpasquer          #+#    #+#             */
/*   Updated: 2017/03/01 21:27:18 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fractol.h"

static int					reset_fractol(t_fractol **f)
{
	if (f == NULL || (*f) == NULL)
		return (false);
	(*f)->c_img_x = 0;
	(*f)->c_img_y = 0;
	(*f)->iter = START_ITER;
	(*f)->zoom = START_ZOOM;
	(*f)->red = START_RED;
	(*f)->green = START_GREEN;
	(*f)->blue = START_BLUE;
	(*f)->x_mouse = WIDTH / 2;
	(*f)->y_mouse = HEIGHT / 2;
	return (true);
}

static int					mouve_img(int key, t_fractol **f)
{
	if (f == NULL || (*f) == NULL)
		return (false);
	if (key == KEY_RIGHT)
		(*f)->c_img_x += MOUVE;
	else if (key == KEY_DOWN)
		(*f)->c_img_y += MOUVE;
	else if (key == KEY_LEFT)
		(*f)->c_img_x -= MOUVE;
	else if (key == KEY_UP)
		(*f)->c_img_y -= MOUVE;
	else if (key == KEY_RESET)
	{
		if (reset_fractol(f) == false)
			return (false);
	}
	else if (key == ITER_PLUS)
		(*f)->iter = (*f)->iter + 1 > MAX_ITER ? (*f)->iter : (*f)->iter + 1;
	else if (key == ITER_MOINS)
		(*f)->iter = (*f)->iter - 1 >= 1 ? (*f)->iter - 1 : (*f)->iter;
	else
		return (false);
	return (g_draw_fractal[(*f)->fractal].f((*f)->x_mouse, (*f)->y_mouse, f));
}

static int					change_colors(int key, t_fractol **f)
{
	if (f == NULL || *f == NULL)
		return (ERROR);
	if (key == RED_PLUS)
		(*f)->red = (*f)->red + 1 <= 255 ? (*f)->red + 1 : (*f)->red;
	else if (key == RED_MOINS)
		(*f)->red = (*f)->red - 1 >= 0 ? (*f)->red - 1: (*f)->red;
	else if (key == GREEN_PLUS)
		(*f)->green = (*f)->green + 1 <= 255 ? (*f)->green + 1 : (*f)->green;
	else if (key == GREEN_MOINS)
		(*f)->green = (*f)->green - 1 >= 0 ? (*f)->green - 1: (*f)->green;
	else if (key == BLUE_PLUS)
		(*f)->blue = (*f)->blue + 1 <= 255 ? (*f)->blue + 1 : (*f)->blue;
	else if (key == BLUE_MOINS)
		(*f)->blue = (*f)->blue - 1 >= 0 ? (*f)->blue - 1: (*f)->blue;
	else
		return (false);
	return (g_draw_fractal[(*f)->fractal].f((*f)->x_mouse, (*f)->y_mouse, f));

}

int							key_hook(int key, void *param)
{
	t_fractol				**f;

	if ((f = (t_fractol **)param) == NULL)
		exit(EXIT_FAILURE);
	if (key == EXIT)
		exit_fractol(param);
	else if (key == KEY_RIGHT || key == KEY_DOWN || key == KEY_LEFT ||
			key == KEY_UP || key == KEY_RESET || key == ITER_PLUS ||
			key == ITER_MOINS)
		return (mouve_img(key, f));
	else if (key == RED_PLUS || key == RED_MOINS || key == GREEN_PLUS ||
			key == GREEN_MOINS || key == BLUE_PLUS || key == BLUE_MOINS )
	{
		if (change_colors(key, f) == ERROR)
			return (ERROR);
	}
	else if (key == KEY_1 && (*f)->fractal != JULIA)
		g_draw_fractal[JULIA].f((*f)->x_mouse, (*f)->y_mouse, f);
	else if (key == KEY_2 && (*f)->fractal != MANDELBROT)
		g_draw_fractal[MANDELBROT].f((*f)->x_mouse, (*f)->y_mouse, f);
	else if (key == KEY_3 && (*f)->fractal != BURNING_SHIP)
		g_draw_fractal[BURNING_SHIP].f((*f)->x_mouse, (*f)->y_mouse, f);
	return (true);
}

int							mouse_hook(int button, int x, int y, void *param)
{
	t_fractol				**f;

	if ((f = (t_fractol **)param) == NULL)
		exit(EXIT_FAILURE);
	if (button == MOUSE_ZOOM_DOWN)
		(*f)->zoom = (*f)->zoom * COEF_ZOOM > MAX_ZOOM ? MAX_ZOOM :
				(*f)->zoom * COEF_ZOOM;
	else if (button == MOUSE_ZOOM_UP)
		(*f)->zoom /= COEF_ZOOM;
	if (button == MOUSE_ZOOM_UP || button == MOUSE_ZOOM_DOWN)
	{
		if ((*f)->zoom == MAX_ZOOM / COEF_ZOOM)
		{
			(*f)->x_mouse = x;
			(*f)->y_mouse = y;
		}
		calcul_coef_mouse(f, x, y);
		return (g_draw_fractal[(*f)->fractal].f((*f)->x_mouse, (*f)->y_mouse, f));
	}
	return (end_loop_fractol(f, (*f)->name, x, y));
}

int							motion_hook(int x, int y, void *param)
{
		t_fractol				**fractol;

	if ((fractol = (t_fractol **)param) == NULL)
		exit(EXIT_FAILURE);
	g_draw_fractal[(*fractol)->fractal].f(x, y, fractol);
	return (true);
}

int							close_hook(int button, void *param)
{
	int						cpy;
	t_fractol				**fractol;

	cpy = button;
	if ((fractol = (t_fractol **)param) == NULL)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
	return (true);
}

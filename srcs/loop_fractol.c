/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_fractol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 09:12:56 by fpasquer          #+#    #+#             */
/*   Updated: 2017/02/19 10:40:05 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fractol.h"

t_draw						g_draw_fractal[] =
{
	{JULIA, draw_julia},
	{MANDELBROT, draw_mandelbrot},
	{BURNING_SHIP, draw_burning_ship},
	{ERROR, NULL},
};

static int					put_color_win(t_fractol *f)
{
	char					str[MAX_STR];
	char					*mem;
	unsigned int			val;

	if (f == NULL || f->mlx == NULL || f->win == NULL)
		return (ERROR);
	val = ft_rgba(f->red, f->green, f->blue, 0);
	if ((mem = ft_itoa_base(val, 16)) == NULL)
		return (false);
	ft_bzero(str, sizeof(str));
	ft_strncpy(str, "Color : #", MAX_STR);
	ft_strncat(str, mem, MAX_STR);
																				//printf("mem = %s\n", mem);
	ft_memdel((void**)&mem);
	mlx_string_put(f->mlx, f->win, 10, 130, COLOR, str);
	return (true);
}

static int					get_nbr_in_str(char str[], char *txt, int nbr)
{
	char					*mem;

	ft_strncpy(str, txt, MAX_STR);
	if ((mem = ft_itoa(nbr)) == NULL)
		return (false);
	ft_strncat(str, mem, MAX_STR);
	ft_memdel((void**)&mem);
	return (true);
}

static int					write_info_fractal(t_fractol *f, int x, int y)
{
	char					str[MAX_STR];

	if (f == NULL || f->mlx == NULL || f->win == NULL)
		return (ERROR);
	ft_strncpy(str, "Nom : ", MAX_STR);
	ft_strncat(str, f->name, MAX_STR);
	mlx_string_put(f->mlx, f->win, 10, 10, COLOR, str);
	if (get_nbr_in_str(str, "X : ", x) == false)
		return (false);
	mlx_string_put(f->mlx, f->win, 10, 40, COLOR, str);
	if (get_nbr_in_str(str, "Y : ", y) == false)
		return (false);
																				//printf("f->zoom = %10.5f\n", f->zoom);
	mlx_string_put(f->mlx, f->win, 10, 70, COLOR, str);
	if (get_nbr_in_str(str, "Iteration : ", f->iter) == false)
		return (false);
	mlx_string_put(f->mlx, f->win, 10, 100, COLOR, str);
	return (put_color_win(f));
}

int							end_loop_fractol(t_fractol **f, char *name,
		int x, int y)
{
	if (f == NULL || (*f) == NULL || (*f)->mlx == NULL || (*f)->win == NULL)
		return (false);
	if ((*f)->name != NULL)
		ft_memdel((void**)&(*f)->name);
	if ((*f)->name == NULL || ft_strcmp(name, (*f)->name) != 0)
		if (((*f)->name = ft_strdup(name)) == NULL)
			return (false);
	mlx_clear_window((*f)->mlx, (*f)->win);
	if (mlx_put_image_to_window((*f)->mlx, (*f)->win, (*f)->img,
			(*f)->c_img_x, (*f)->c_img_y) == false)
		return (false);
																				//printf("x_img = %d, y_img = %d\n", (*f)->c_img_x, (*f)->c_img_y);
	return (write_info_fractal(*f, x, y));
}

void						loop_fractol(t_fractol *fractol)
{
	if (fractol == NULL)
		exit(EXIT_FAILURE);
	mlx_key_hook(fractol->win, key_hook, &fractol);
	mlx_mouse_hook(fractol->win, mouse_hook, &fractol);
	mlx_hook(fractol->win, 6, 64, motion_hook, &fractol);
	mlx_hook(fractol->win, 17, 0, close_hook, &fractol);
	mlx_hook(fractol->win, 2, 1, key_hook, &fractol);
	mlx_loop(fractol->mlx);
}

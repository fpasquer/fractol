/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 23:00:10 by fpasquer          #+#    #+#             */
/*   Updated: 2017/02/26 21:47:42 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fractol.h"

int							turn_on_pixel(t_fractol **f, int x_tab, int y_tab,
		int color)
{
	if (f == NULL || *f == NULL)
		return (ERROR);
	if ((*f)->data == NULL)
		return (ERROR);
	(*f)->data[y_tab * (int)WIDTH + x_tab] = color;
	return (true);
}

int							print_man(void)
{
	ft_putstr("Voici la liste des fractals disponible :\n");
	ft_putstr("1 : Julia\n");
	ft_putstr("2 : Mandelbrot\n");
	return (EXIT_FAILURE);
}

int							main(int argc, char **argv)
{
	t_fractol				*fractol;

	if (argc == 1)
		return (print_man());
	if ((fractol = init_fractol(argv[1])) == NULL)
		return (print_man());
	loop_fractol(fractol);
	return (EXIT_SUCCESS);
}

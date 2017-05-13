/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fractol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 09:12:39 by fpasquer          #+#    #+#             */
/*   Updated: 2017/03/12 09:19:31 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fractol.h"

void						exit_fractol(void *param)
{
	t_fractol				**fractol;

	if ((fractol = (t_fractol **)param) == NULL)
		exit(EXIT_FAILURE);
	del_fractol(fractol);
	exit(EXIT_SUCCESS);
}

int							del_fractol(t_fractol **fractol)
{
	if (fractol == NULL || *fractol == NULL)
		return (false);
	if ((*fractol)->name != NULL)
		ft_memdel((void**)&(*fractol)->name);
	if ((*fractol)->img != NULL)
		mlx_destroy_image((*fractol)->mlx, (*fractol)->img);
	if ((*fractol)->win != NULL)
		mlx_destroy_window((*fractol)->mlx, (*fractol)->win);
	//if ((*fractol)->mlx != NULL)
	//	ft_memdel((void**)&(*fractol)->mlx);
	ft_memdel((void**)fractol);
	return (true);
}

int							check_name(char *name)
{
	if (ft_strcmp(name, "julia") == 0)
		return (JULIA);
	else if (ft_strcmp(name, "mandelbrot") == 0)
		return (MANDELBROT);
	else if (ft_strcmp(name, "burning ship") == 0)
		return (BURNING_SHIP);
	return (ERROR);
}

t_fractol					*init_mlx(t_fractol **ret)
{
	if (ret == NULL || *ret == NULL || (*ret)->name == NULL)
		return (NULL);
	if (((*ret)->mlx = mlx_init()) == NULL)
		return (NULL);
	if (((*ret)->win = mlx_new_window((*ret)->mlx, WIDTH, HEIGHT,
			FRACTOL_NAME)) == NULL)
		return (NULL);
	if (((*ret)->img = mlx_new_image((*ret)->mlx, WIDTH, HEIGHT)) == NULL)
		return (NULL);
	if (((*ret)->data = (int*)mlx_get_data_addr((*ret)->img, &(*ret)->t[0],
			&(*ret)->t[1], &(*ret)->t[2])) == NULL)
		return (NULL);
	if ((g_draw_fractal[(*ret)->fractal].f(0, 0, ret)) == false)
		return (NULL);
	return (*ret);
}

t_fractol					*init_fractol(char *name)
{
	unsigned int			i;
	t_fractol				*ret;

	if (name == NULL || (ret = ft_memalloc(sizeof(t_fractol))) == NULL)
		return (NULL);
	i = 0;
	while (name[i++] != '\0')
		name[i - 1] = ft_tolower(name[i - 1]);
	if ((ret->name = ft_strdup(name)) == NULL)
		return (NULL);
	if ((ret->fractal = check_name(ret->name)) == ERROR)
	{
		del_fractol(&ret);
		return (NULL);
	}
	ret->iter = START_ITER;
	ret->red = START_RED;
	ret->green = START_GREEN;
	ret->blue = START_BLUE;
	ret->zoom = START_ZOOM;
	ret->x_mouse = WIDTH / 2;
	ret->y_mouse = HEIGHT / 2;
	return (init_mlx(&ret));
}

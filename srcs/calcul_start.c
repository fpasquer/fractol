/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:44:35 by fpasquer          #+#    #+#             */
/*   Updated: 2017/03/04 13:34:25 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/fractol.h"

static unsigned int			get_len_zoom(double zoom)
{
	unsigned int			ret;

	ret = 1;
	while (zoom * COEF_ZOOM <= MAX_ZOOM)
	{
		zoom *= COEF_ZOOM;
		ret++;
	}
	return (ret);
}

static double				new_total(int base, int coef)
{
	double					ret;

	ret = (double)base;
	while (coef-- > 1)
		ret /= COEF_ZOOM;
	return (ret);
}

double						get_curent_position(double min, double max,
		double mouse, double total)
{
	double					tmp_min;
	double					tmp_max;
	int						tmp_mouse;
	double					gap;

	tmp_min = (min < 0) ? min * -1.0 : min;
	tmp_max = (max < 0) ? max * -1.0 : max;
	gap = tmp_min + tmp_max;
	tmp_mouse = (mouse < 0) ? 0 : mouse;
	tmp_mouse = (tmp_mouse > total) ? total : tmp_mouse;
	return (min + (double)tmp_mouse * gap / total);
}

int							calcul_coef_mouse(t_fractol **f, int x, int y)
{
	unsigned int			len_zoom = 0;

	return (true);
	if (f == NULL || *f == NULL)
		return (ERROR);
	if (x != (*f)->x_mouse + (*f)->decalage_x || y != (*f)->y_mouse + (*f)->decalage_y)
	{
		(*f)->decalage_x = x - (*f)->x_mouse;
		(*f)->decalage_y = y - (*f)->y_mouse;
		if ((len_zoom = get_len_zoom((*f)->zoom)) > 1)
		{
																				printf("Line %d ", __LINE__);
			(*f)->percent_x = (*f)->decalage_x - 250;
			(*f)->percent_y = (*f)->decalage_y - 200;
		}
		else
		{
																				printf("Line %d ", __LINE__);
			(*f)->percent_x = 0.0;
			(*f)->percent_y = 0.0;
		}
	}
	else if ((len_zoom = get_len_zoom((*f)->zoom)) == 1)
	{
																				printf("Line %d ", __LINE__);
		(*f)->percent_x = 0.0;
		(*f)->percent_y = 0.0;
	}
	else
																				printf("Line %d ", __LINE__);
																				printf("x_mouse %4d decalage_x %3d percent_x %2.5f old_new_width = %3.5f new_width = %3.5f, new_x %3.5f\n", (*f)->x_mouse, (*f)->decalage_x, (*f)->percent_x, new_total(WIDTH, len_zoom - 1), new_total(WIDTH, len_zoom), (*f)->x_mouse + (*f)->percent_x);
	return (true);
}

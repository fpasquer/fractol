/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 23:02:55 by fpasquer          #+#    #+#             */
/*   Updated: 2017/03/04 13:51:04 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H

# define FRACTOL_H

# include <stdlib.h>
# include <stdbool.h>
# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>

typedef enum				e_fractal
{
	ERROR = -1,
	JULIA = 0,
	MANDELBROT = 1,
	BURNING_SHIP = 2
}							t_fractal;

# define W_INFO 300
# define H_INFO 150
# define MAX_STR 1000
# define COLOR 0x00FFFFFF

# define EXIT 53

# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_RESET 15 //r
# define ITER_PLUS 122 //f1
# define ITER_MOINS 120 //f2
# define ZOOM_PLUS 89
# define ZOOM_MOINS 89
# define RED_PLUS 12//q
# define RED_MOINS 13//w
# define GREEN_PLUS 0//z
# define GREEN_MOINS 1//x
# define BLUE_PLUS 6//a
# define BLUE_MOINS 7//s

# define MOUSE_ZOOM_DOWN 4
# define MOUSE_ZOOM_UP 5

# define START_RED 249
# define START_GREEN 8
# define START_BLUE 8
# define START_ZOOM 1
# define MAX_ZOOM 1
# define COEF_ZOOM 1.1

# define MOUVE 10

# define FRACTOL_NAME "Fractol"

# define CL(v) (unsigned int)((v * p.i) * 33.78) % 255

# define MAX_ITER 1300
# define START_ITER 50
# define WIDTH 640
# define HEIGHT 480

typedef struct				s_pixel
{
	int						max_iter;
	double					x1;
	double					x2;
	double					y1;
	double					y2;
	double					zoom_x;
	double					zoom_y;
	double					c_r;
	double					c_i;
	double					z_r;
	double					z_i;
	double					i;
	double					tmp;

}							t_pixel;

typedef struct				s_fractol
{
	void					*mlx;
	void					*win;
	void					*w_info;
	void					*img;
	char					*name;
	unsigned char			red;
	unsigned char			blue;
	unsigned char			green;
	int						*data;
	int						**data_2d;
	int						t[3];
	int						iter;
	int						c_img_y;
	int						c_img_x;
	int						x_mouse;
	int						y_mouse;
	int						x;
	int						y;
	int						decalage_x;
	int						decalage_y;
	double					zoom;
	double					percent_x;
	double					percent_y;
	t_fractal				fractal;
}							t_fractol;

typedef struct				s_draw
{
	int						i;
	int						(*f)(int, int, t_fractol **);
}							t_draw;


t_draw						g_draw_fractal[4];

t_fractol					*init_fractol(char *name);
void						loop_fractol(t_fractol *fractol);
int							del_fractol(t_fractol **fractol);
void						exit_fractol(void *param);

double						get_curent_position(double min, double max,
		double mouse, double total);
int							calcul_coef_mouse(t_fractol **f, int x, int y);

int							key_hook(int key, void *param);
int							mouse_hook(int button, int x, int y, void *param);
int							motion_hook(int x, int y, void *param);
int							close_hook(int button, void *param);

int							draw_julia(int x_mouse, int y_mouse,
		t_fractol **fractol);
int							draw_mandelbrot(int x_mouse, int y_mouse,
		t_fractol **fractol);
int							draw_burning_ship(int x_mouse, int y_mouse,
		t_fractol **fractol);

int							end_loop_fractol(t_fractol **f, char *name,
		int x, int y);

int							turn_on_pixel(t_fractol **f, int x_tab, int y_tab,
		int color);

#endif

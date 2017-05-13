/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgba.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 22:28:40 by fpasquer          #+#    #+#             */
/*   Updated: 2017/02/18 10:44:19 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int				ft_rgba(unsigned char red, unsigned char green,
		unsigned char blue, unsigned char trans)
{
	unsigned int			ret;

	ret = (trans << 24);
	ret += (red << 16);
	ret += (green << 8);
	ret += (blue);
	return (ret);
}

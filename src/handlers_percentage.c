/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_percentage.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 23:40:40 by psergio-          #+#    #+#             */
/*   Updated: 2021/07/02 23:40:40 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	print_percent(t_param *param)
{
	if (param->width > param->str_len)
		if (fill_int_width(param) < 0)
			return (-1);
	write(1, param->str, param->str_len);
	return (param->str_len);
}

void	handle_percentage(t_param *param)
{
	param->specifier = '%';
	param->str = ft_strdup("%");
}

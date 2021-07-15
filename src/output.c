/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 00:24:17 by psergio-          #+#    #+#             */
/*   Updated: 2021/06/29 00:24:17 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	fill_width(t_param *param)
{
	char	*new_str;
	int		i;

	new_str = malloc(param->width + 1);
	if (new_str == NULL)
		return (-1);
	i = 0;
	if (!param->minus)
		while (i < (int)(param->width - param->str_len))
			new_str[i++] = ' ';
	new_str[i] = '\0';
	ft_strlcat(new_str, param->str, param->width + 1);
	i = param->str_len;
	if (param->minus)
	{
		while (i < (int)(param->width))
			new_str[i++] = ' ';
		new_str[i] = '\0';
	}
	free(param->str);
	param->str = new_str;
	param->str_len = param->width;
	return (1);
}

int	print_param(t_param *param)
{
	if (param->specifier == 'c')
		return (print_char(param));
	if (param->specifier == 'd')
		return (print_int(param));
	if (param->specifier == 'i')
		return (print_inti(param));
	if (param->specifier == 'u')
		return (print_intu(param));
	if (param->specifier == 'x')
		return (print_hex(param));
	if (param->specifier == 'X')
		return (print_hex(param));
	if (param->specifier == '%')
		return (print_percent(param));
	if (param->str_len < param->width)
		if (fill_width(param) < 0)
			return (-1);
	write (1, param->str, param->str_len);
	return (param->str_len);
}

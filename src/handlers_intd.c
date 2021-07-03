/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_intd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 18:18:07 by psergio-          #+#    #+#             */
/*   Updated: 2021/07/02 18:18:07 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	fill_precision(t_param *param)
{
	int		i;
	int		str_len;
	char	*new_str;
	int		is_neg;

	is_neg = param->str[0] == '-';
	str_len = ft_strlen(param->str);
	if (str_len >= param->precision)
		return (str_len);
	new_str = malloc(param->precision + is_neg + 1);
	if (new_str == NULL)
		return (-1);
	i = 0;
	if (is_neg)
		new_str[i++] = '-';
	while (i < param->precision - str_len + is_neg)
		new_str[i++] = '0';
	new_str[i + is_neg] = '\0';
	ft_strlcat(new_str, param->str + is_neg, param->precision + 1 + is_neg);
	free(param->str);
	param->str = new_str;
	param->str_len = param->precision + is_neg;
	return (param->precision);
}

int	print_intd(t_param *param)
{
	if (param->has_precision)
		if (fill_precision(param) < 0)
			return (-1);
	if (param->width > param->str_len)
		if (fill_width(param) < 0)
			return (-1);
	write(1, param->str, param->str_len);
	return (param->str_len);
}

void	handle_intd(t_param *param, va_list ap)
{
	param->specifier = 'd';
	param->str = ft_itoa(va_arg(ap, int));
}

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

static int	handle_zero(t_param *param)
{
	if (param->str[0] == '0')
	{
		free(param->str);
		param->str = ft_strdup("");
		param->str_len = 0;
	}
	return (param->precision);
}

static int	fill_precision(t_param *param)
{
	int		i;
	int		str_len;
	char	*new_str;
	int		is_neg;

	if (param->precision == 0)
		return (handle_zero(param));
	is_neg = param->str[0] == '-';
	str_len = ft_strlen(param->str);
	if (str_len >= param->precision + is_neg)
		return (str_len);
	new_str = malloc(param->precision + is_neg + 1);
	if (new_str == NULL)
		return (-1);
	i = 0;
	if (is_neg)
		new_str[i] = '-';
	while (i < param->precision - str_len + is_neg)
		new_str[i++ + is_neg] = '0';
	new_str[i + is_neg] = '\0';
	ft_strlcat(new_str, param->str + is_neg, param->precision + 1 + is_neg);
	free(param->str);
	param->str = new_str;
	param->str_len = param->precision + is_neg;
	return (param->precision);
}

int	print_inti(t_param *param)
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

void	handle_inti(t_param *param, va_list ap)
{
	param->specifier = 'i';
	param->str = ft_itoa(va_arg(ap, int));
}

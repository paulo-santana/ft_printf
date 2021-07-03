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

	str_len = ft_strlen(param->str);
	if (str_len >= param->precision)
		return (str_len);
	new_str = malloc(param->precision + 1);
	if (new_str == NULL)
		return (-1);
	i = 0;
	new_str[param->precision] = '\0';
	while (i < param->precision - str_len)
		new_str[i] = '0';
	new_str[i] = '\0';
	ft_strlcat(new_str, param->str, param->precision);
	free(param->str);
	param->str = new_str;
	return (param->precision);
}

int	print_inti(t_param *param)
{
	if (param->has_precision)
		fill_precision(param);
	return (0);
}

void	handle_inti(t_param *param, va_list ap)
{
	param->str = ft_itoa(va_arg(ap, int));
}

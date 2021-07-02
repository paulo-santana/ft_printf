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

static int	fill_str(t_param *param, int str_len)
{
	char	*new_str;
	int		i;

	new_str = malloc(param->width + 1);
	if (new_str == NULL)
		return (-1);
	i = 0;
	while (i < param->width - str_len)
		new_str[i++] = ' ';
	new_str[i] = '\0';
	ft_strlcat(new_str, param->str, param->width + 1);
	free(param->str);
	param->str = new_str;
	return (1);
}

int	print_param(t_param *param)
{
	int	len;

	len = ft_strlen(param->str);
	if (len < param->width)
	{
		if (fill_str(param, len) < 0)
			return (-1);
		len = param->width;
	}
	if (param->has_precision)
		if (len > param->precision)
			len = param->precision;
	write (1, param->str, len);
	return (len);
}

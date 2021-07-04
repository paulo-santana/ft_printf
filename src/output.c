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
	while (i < (int)(param->width - param->str_len))
		new_str[i++] = ' ';
	new_str[i] = '\0';
	ft_strlcat(new_str, param->str, param->width + 1);
	free(param->str);
	param->str = new_str;
	param->str_len = param->width;
	return (1);
}

int	print_param(t_param *param)
{
	if (param->specifier == 'd')
		return (print_intd(param));
	if (param->specifier == 'i')
		return (print_inti(param));
	if (param->str_len < param->width)
		if (fill_width(param) < 0)
			return (-1);
	write (1, param->str, param->str_len);
	return (param->str_len);
}

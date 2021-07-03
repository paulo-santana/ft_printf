/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 22:52:39 by psergio-          #+#    #+#             */
/*   Updated: 2021/07/02 22:52:39 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char	*char_to_str(int c)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = (char)c;
	return (str);
}

void	handle_char(t_param *param, va_list ap)
{
	param->specifier = 'c';
	param->str = char_to_str(va_arg(ap, int));
}

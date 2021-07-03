/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 23:30:59 by psergio-          #+#    #+#             */
/*   Updated: 2021/07/02 23:30:59 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	handle_hex(t_param *param, va_list ap)
{
	param->specifier = 'x';
	param->str = ft_itox(va_arg(ap, unsigned int));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 11:03:07 by psergio-          #+#    #+#             */
/*   Updated: 2021/06/22 17:44:45 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

/* TODO: criar funções que verificam cada parte do placeholder
 * (flag, width, .precision, length e type) e gera os metadados necessarios 
 * para escrita na tela. */

static int	print_placeholder(const char **format, va_list ap)
{
	t_param	*param;
	int		chars_printed;

	param = get_data(*format + 1, ap);
	chars_printed = print_param(param);
	*format = *format + param->placeholder_len;
	free(param->str);
	free(param);
	return (chars_printed);
}

int	ft_printf(const char *format, ...)
{
	int			chars_printed;
	va_list		ap;
	const char	*next_spec;

	chars_printed = 0;
	va_start(ap, format);
	while (format)
	{
		next_spec = ft_strchr(format, '%');
		if (next_spec)
		{
			write(1, format, next_spec - format);
			chars_printed += next_spec - format;
			chars_printed += print_placeholder(&next_spec, ap);
			format = next_spec + 1;
		}
		else
		{
			ft_putstr_fd((char *)format, 1);
			chars_printed += ft_strlen(format);
			break ;
		}
	}
	va_end(ap);
	return (chars_printed);
}
